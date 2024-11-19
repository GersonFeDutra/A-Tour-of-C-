#include <string>
#include <vector>
#include <list>
#include <iostream>
using std::literals::string_literals::operator"" s;

template <typename T> class Less_than
{
	const T val;
	// value to compare against
public:
	Less_than(const T &v) : val{v}
	{
	}
	bool operator()(const T &x) const
	{
		return x < val;
	} // call operator
};

void fct(int n, const std::string &s)
{

	Less_than lti{42};        // lti(i) will compare i to 42 using < (i<42)
	Less_than lts{"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")
	Less_than<std::string> lts2{
		"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <

	bool b1 = lti(n);
	bool b2 = lts(s);
	// ...
}

template <typename C, typename P>
// requires Sequence<C> && Callable<P,Value_type<P>>
int count(const C &c, P pred)
{
	int cnt = 0;
	for (const auto &x : c)
		if (pred(x))
			++cnt;
	return cnt;
}

void f(const std::vector<int> &vec, const std::list<std::string> &lst, int x, const std::string &s)
{
	std::cout << "number of values less than " << x << ": " << count(vec, Less_than{x}) << '\n';
	std::cout << "number of values less than " << s << ": " << count(lst, Less_than{s}) << '\n';
}


int main(void)
{
	fct(2, "test");
    f(std::vector{1, 2, 3}, std::list{"a"s, "b"s, "c"s}, 2, "b");
}
