#include <algorithm>
#include <concepts>
#include <ranges>
// utils
#include <complex>
#include <iostream>
#include <vector>

using namespace std::ranges;

template <forward_range R>
	requires std::sortable<iterator_t<R>>
void my_sort(R &r) // modern, concept-constrained version of my_sort
{
	return my_sort(r.begin(), r.end()); // use the 1994-style sort
}


namespace ex1
{
void user(forward_range auto &r)
{
	filter_view v{r, [](int x) { return x % 2; }}; // view (only) odd numbers from r

	std::cout << "odd numbers: ";
	for (int x : v)
		std::cout << x << ' ';
}
} // namespace ex1

namespace ex2
{
void user(forward_range auto &r)
{
	filter_view v{r, [](int x) { return x % 2; }}; // view (only) odd numbers from r
	take_view tv{v, 100};                          // view at most 100 elements from v

	std::cout << "odd numbers: ";
	for (int x : tv)
		std::cout << x << ' ';
}
} // namespace ex2

namespace ex3
{
void user(forward_range auto &r)
{
	filter_view v{r, [](int x) { return x % 2; }}; // view (only) odd numbers from r

	std::cout << "odd numbers: ";
	for (int x : take_view{v, 3}) // avoid naming the take_view by using directly
		std::cout << x << ' ';

	// or even (bad idea)
	/*
	std::cout << "odd numbers: ";
	for (int x : take_view{filter_view{r, [](int x) { return x % 2; }}, 3}) // avoid naming the
	    take_view by using directly std::cout << x << ' ';
	*/
}

auto bad()
{
	constexpr auto odd = [](int x) { return x % 2; };
	std::vector v = {1, 2, 3, 4};
	return filter_view{v, odd}; // v will be destroyed before the view
}
} // namespace ex3


namespace ex4
{
struct Reading {
	int location{};
	int temperature{};
	int humidity{};
	int air_pressure{};
	// ...
};

struct No_readings {
};

int average_temp(std::vector<Reading> readings)
{
	if (readings.empty())
		throw No_readings{};
	double s = 0;

	for (int x : views::elements<1>(readings)) // look at just the temperatures
		s += x;
	return s / readings.size();
}
} // namespace ex4


namespace generators
{
int main()
{
	for (int x : iota_view(42, 52)) // 42 43 44 45 46 47 48 49 50 51
		std::cout << x << ' ';

	for (auto x : istream_view<std::complex<double>>(std::cin))
		std::cout << x << '\n'; // read from standard input

	// composite views
	auto cplx = istream_view<std::complex<double>>(std::cin);
	for (auto x : transform_view(cplx, [](auto z) { return z * z; }))
		std::cout << x << '\n';
}
} // namespace generators

namespace pipelines
{
void user(forward_range auto &r)
{
	/* bad
	for (int x : r | views::filter([](int x) { return x % 2; }) | views::take(3))
	    std::cout << x << ' ';
	*/

	/* ok
	auto odd = [](int x) { return x % 2; };

	for (int x : r | views::filter(odd) | views::take(3))
	    std::cout << x << ' ';
	*/
	/* better */
	using namespace views;

	auto odd = [](int x) { return x % 2; };

	for (int x : r | filter(odd) | take(3))
		std::cout << x << ' ';

	/* equivalent */
	int cout = 0;
	for (int x : r)
		if (x % 2) {
			std::cout << x << ' ';
			if (++cout == 3)
				return;
		}
}

} // namespace pipelines


template <typename B>
concept Boolean = requires(B x, B y) {
	{ x = true };
	{ x = false };
	{ x = (x == y) };
	{ x = (x != y) };
	{ x = !x };
	{ x = (x = y) };
};

template <class Iter> class Sentinel
{
public:
	Sentinel(int ee) : end(ee)
	{
	}
	Sentinel() : end(0)
	{
	} // Concept sentinel_for requires a default constructor

	friend bool operator==(const Iter &p, Sentinel s)
	{
		return (*p == s.end);
	}
	friend bool operator!=(const Iter &p, Sentinel s)
	{
		return !(p == s);
	}

private:
	iter_value_t<const char *> end; // the sentinel value
};

static_assert(std::sentinel_for<Sentinel<const char *>,
	const char *>); // check the Sentinel for C-style strings

void test()
{
	const char aa[] = "Hello, World!\nBye for now\n";

	for_each(aa, Sentinel<const char *>('\n'), [](const char x) { std::cout << x; });
}

int main()
{
	std::vector v(125, [](int i) { return i; });
	ex1::user(v);
	ex2::user(v);
	ex3::user(v);
	generators::main();
	pipelines::user(v);

	test();
}
