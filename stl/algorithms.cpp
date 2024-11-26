#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
// algorithms
#include <algorithm>
#include <execution>
#include <ranges>


using std::copy, std::unique_copy;
using std::find, std::find_if;
using std::for_each, std::for_each_n;
using std::sort;

using std::ostream_iterator, std::istream_iterator;


struct Entry {
	std::string name;
	int number;
};

bool operator<(const Entry &x, const Entry &y) // less than
{
	return x.name < y.name; // order Entries by their names
}


void f(std::vector<Entry> &vec, std::list<Entry> &lst)
{
	sort(vec.begin(), vec.end());                     // use < for order
	unique_copy(vec.begin(), vec.end(), lst.begin()); // don't copy adjacent equal elements
}


std::list<Entry> f(std::vector<Entry> &vec)
{
	std::list<Entry> res;
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), back_inserter(res)); // append to res
	return res;
}


template <typename C> class Checked_iter
{
public:
	using value_type = typename C::value_type;
	using difference_type = int;

	/*************  ✨ Codeium Command ⭐  *************/
	/// Construct a Checked_iter without a container.
	/// This is useful when Checked_iter is used as a return type
	/// and the function needs to return an error.
	/// This constructor throws a Missing_container.
	/******  d7fadc25-e01d-4e15-82e0-bcef42170bdc  *******/
	Checked_iter()
	{
		throw Missing_container{};
	} // concept forward_iterator requires a default constructor
	Checked_iter(C &cc) : pc{&cc}
	{
	}

	Checked_iter(C &cc, typename C::iterator pp) : pc{&cc}, p{p}
	{
	}

	Checked_iter &operator++()
	{
		check_end();
		++p;
		return *this;
	}
	Checked_iter(C &&cc, typename C::iterator pp) : pc{&cc}, p{pp}
	{
	}

	Checked_iter &operator++()
	{
		checked_end();
		++p;
		return *this;
	}
	// post-increment: make a copy and increment this iterator
	// checked that we have not reached the end of the container
	Checked_iter operator++(int)
	{
		checked_end();
		auto t{*this};
		++p;
		return t;
	}
	value_type &operator*() const
	{
		checked_end();
		return *p;
	}

	bool operator==(const Checked_iter &a) const
	{
		return p == a.p;
	}
	bool operator!=(const Checked_iter) const
	{
		return p != a.p;
	}

private:
	void check_end() const
	{
		if (p == pc->end())
			throw Overflow{};
	}
	C *pc{}; // default initialize to nullptr
	typename C::iterator p = pc->begin();
};


bool has_c(const std::string &s, char c) // does s contain the character c?
{
	return find(s.begin(), s.end(), c) != s.end();
}

std::vector<std::string::iterator> find_all(std::string &s, char c) // find all positions of c in s
{
	std::vector<char *> res;
	for (auto p = s.begin(); p != s.end(); ++p)
		if (*p == c)
			res.push_back(p);
	return res;
}


void test()
{
	std::string m{"Mary had a little lamb"};
	for (auto p : find_all(m, 'a'))
		if (*p = 'a')
			std::cerr << "a bug!\n";
}


template <typename C, typename V>
std::vector<typename C::iterator> find_all(C &c, V v) // find all occurrences of v in c
{
	std::vector<typename C::iterator> res;
	for (auto p = c.begin(); p != c.end(); ++p)
		if (*p == v)
			res.push_back(p);
	return res;
}

/* alternative */
namespace alternative
{

template <typename T> using range_value_t = typename T::value_type;

template <typename C, typename V>
std::vector<typename C::iterator> find_all(C &c, V v) // find all occurrences of v in c
{
	std::vector<range_value_t<C> *> res;
	for (auto &x : c)
		if (x == v)
			res.push_back(&x);
	return res;
}

void test()
{
	std::string m{"Mary had a little lamb"};

	for (auto p : find_all(m, 'a')) // p is a string::iterator
		if (*p == 'a')
			std::cerr << "string bug!\n";

	std::list<int> id{1, 2, 3, 1, -11, 2};
	for (auto p : find_all(id, 1)) // p is a list<int>::iterator
		if (*p != 1)
			std::cerr << "list bug!\n";

	std::vector<std::string> vs{"red", "blue", "green", "orange", "green"};
	for (auto p : find_all(vs, "red")) // p is a vector<string>::iterator
		if (*p != "red")
			std::cerr << "vector bug!\n";

	for (auto p : find_all(vs, "green"))
		*p = "vert";
}

} // namespace alternative


namespace ex
{
int main()
{
	std::string from, to;
	std::cin >> from >> to; // get source and target file names

	std::ifstream is{from};               // input stream for file "from"
	istream_iterator<std::string> ii{is}; // input iterator for stream
	istream_iterator<std::string> eos{};  // input sentinel

	std::ofstream os{to};                       // output stream for file "to"
	ostream_iterator<std::string> oo{os, "\n"}; // output iterator for stream plus a separator

	// std::vector<std::string> b{ii, eos}; // b is a vector initialized from input
	//  sort(b.begin(), b.end());            // old version
	// std::ranges::sort(b); // sort the buffer

	std::set<std::string> b{ii, eos}; // b is a set initialized from input


	// std::ranges::unique_copy(b, oo); // copy the buffer to output, discard replicated values
	std::ranges::copy(b, oo); // copy buffer to output

	return !is.eof() || !os; // return error state
}

} // namespace ex


namespace ex2
{

int main()
{
	std::string from, to;
	std::cin >> from >> to; // get source and target file names

	std::ifstream is{from}; // input stream for file "from"
	std::ofstream os{to};   // output stream for file "to"

	std::set<std::string> b{
		std::istream_iterator<std::string>{is}, std::istream_iterator<std::string>{}}; // read input
	std::ranges::copy(b, ostream_iterator<std::string>{os, "\n"}); // write output

	return !is.eof() || !os; // return error state
}

} // namespace ex2


struct Greater_than {
	int val;
	Greater_than(int v) : val{v}
	{
	}
	bool operator()(const std::pair<std::string, int> &r) const
	{
		return r.second > val;
	}
};

void f(std::map<std::string, int> &m)
{
	auto p = std::ranges::find_if(m, Greater_than{42});

	auto p2 = std::ranges::find_if(m, [](const auto &r) { return r.second > 42; });
	// ...
}

namespace std::ranges
{
void sort(auto policy, random_access_range auto &r)
{
	std::sort(pol, r.begin(), r.end());
}
} // namespace std::ranges


int main()
{
	std::vector<Entry> phone_book = {
		{"David Hume", 1234456},
		{"Karl Popper", 234567},
		{"Bertrand Arthur William Russel", 345678},
	};
	std::list<Entry> phone_book2(phone_book.size());

	std::vector<int> v1{1, 2, 3}; // three elements
	std::vector<int> v2(2);       // will overflow

	copy(v1.begin(), v1.end(), v2.begin());       // will overflow
	copy(v1.begin(), v1.end(), Checked_iter{v2}); // will throw

	f(phone_book, phone_book2);
	phone_book2 = f(phone_book);

	has_c(phone_book[0].name, 'a');

	test();
	alternative::test();

	ostream_iterator<std::string> oo{cout}; // write strings to cout

	*oo = "Hello, "; // meaning cout << "Hello, "
	++o;
	*oo = "world!\n"; // meaning cout << "world\n"

	std::vector<std::string> v{"Hello,", ", ", "world!\n"};
	copy(v.begin(), v.end(), oo);

	int err = ex::main();

	std::vector<int> v = {0, 1, 2, 3, 4, 5};
	std::ranges::for_each(v, [](int &x) { x = x * x; });                  // 0, 1, 4,9, 16, 25
	for_each(v.begin(), v.begin() + 3, [](int &x) { x = std::sqrt(x); }); // 0, 1, 2

	sort(v.begin(), v.end());                            // sequential
	sort(std::execution::seq, v.begin(), v.end());       // sequential (same as the default)
	sort(std::execution::seq, v.begin(), v.end());       // sequential (same as the default)
	sort(std::execution::par, v.begin(), v.end());       // parallel
	sort(std::execution::par_unseq, v.begin(), v.end()); // parallel and/or vectorized

	return err;
}
