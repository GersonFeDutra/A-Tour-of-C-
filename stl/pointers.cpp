#include <any>
#include <array>
#include <bitset>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>
// utils
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>
#include <ranges>
#include <string>

using std::any;
using std::bitset;
using std::optional;
using std::pair;
using std::shared_ptr;
using std::span;
using std::tuple;
using std::unique_ptr;
using std::variant;
using std::weak_ptr;

using std::any_cast;
using std::make_shared, std::make_unique;
using std::make_tuple;

enum class Error_code {
	found,
	good,
	not_found,
};

namespace ex1_mutex
{
std::mutex m; // used to protect access to shared data

void f()
{
	std::scoped_lock lck{m}; // acquire mutex m
	                         // ... manipulate shared data ...
}
} // namespace ex1_mutex

namespace ex2_smart_pointers
{
struct X {
	int i;
};
struct Z : std::exception {
};

void f(int i, int j) // X* vs. unique_ptr<X>
{
	// why not just don't use a pointer?
	X *p = new X;            // allocate a new X
	unique_ptr<X> sp{new X}; // allocate a new X and give its pointer to unique_ptr
	// ...

	// p will b e leaked by those ifs
	if (i < 99)
		throw Z{}; // may throw an exception
	if (j < 77)
		return; // may return "early"
	// ... use p and sp ...
	delete p; // destroy *p, otherwise leak
}

unique_ptr<X> make_X(int i)
// make an X and immediately give it to a unique_ptr
{
	// ... check i, etc ...
	return unique_ptr<X>{new X{i}};
}

void f(shared_ptr<std::fstream>);
void g(shared_ptr<std::fstream>);

struct No_file : std::exception {
};

void user(const std::string &name, std::ios_base::openmode mode)
{
	shared_ptr<std::fstream> fp{new std::fstream{name, mode}};
	if (!*fp) // make sure the file was properly opened
		throw No_file{};

	f(fp);
	g(fp);
	// ...
}

struct S {
	int i;
	std::string s;
	double d;
}; // ...

auto p1 = make_shared<S>(1, "Ankh Morpork", 4.65); // p1 is a shared_ptr<S>
auto p2 = make_unique<S>(2, "Oz", 7.62);           // p2 is a unique_ptr<S>"

void fpn(int *p, int n)
{
	/* basic */
	for (int i = 0; i < n; ++i)
		p[i] = 0;
	/* better */
	for (int *q = p; q < p + n; ++q)
		*q = 0;
}

void use(int x)
{
	int a[100];
	fpn(a, 100);      // OK
	fpn(a, 1000);     // oops, my finger slipped! (range error in fpn)
	fpn(a + 10, 100); // range error in fpn
	fpn(a, x);        // suspect, but looks innocent
}
} // namespace ex2_smart_pointers

namespace ex3_span
{
void fs(span<int> p)
{
	for (int &x : p)
		x = 0;
}

void use(int x)
{
	int a[100];
	fs(a);             // implicitly creates a span<int>{a, 100}
	fs(a, 1000);       // error: span expected
	fs({a + 10, 100}); // a range error in fs
	fs{a, x};          // obviously suspect
}

void f1(span<int> p);

void f2(span<int> p)
{
	// ...
	f1(p);
}

int main()
{
	using std::array;
	array<int, 3> a1 = {1, 2, 3};
	array<int> a0 = {1, 2, 3};                      // error: size not specified
	int n = 2;                                      // use a vector if you need a dynamic size
	array<std::string, n> = {"John's", "Queens' "}; // error: size not a constant expression
	array<std::string, 0> a2;                       // error: size must be positive
	array<2> a3 = {"John's", "Queens' "};           // error: element type not stated

	array a2 = {1, 2, 3}; // ok, implicitly converted to array<int, 3>

	return 0;
}
} // namespace ex3_span

namespace ex4_array
{
using std::array;

namespace ex_a
{
void f(int *p, int sz); // C-style interface

void g()
{
	array<int, 10> a;
	f(a, a.size);          // error: no conversion
	f(a.data(), a.size()); // C-style use

	auto p = std::ranges::find(a, 777); // C++/ STL-style use (a range is passed)
}

void h()
{
	array<int, 3> a1 = {1, 2, 3};
	auto a2 = a1; // copy
	a2[1] = 5;
	a1 = a2; // assign
}
} // namespace ex_a

namespace ex_b
{
using std::array;

struct Shape {
	int x, y;

	void draw()
	{
	}
};
struct Circle : Shape {
	int radius;
};
void h()
{
	Circle a1[10];
	array<Circle, 10> a2;
	// ...
	Shape *p1 = a1; // OK: disaster waiting to happen
	Shape *p2 = a2; // error: no conversion of array<Circle, 10> to Shape* (Good!)
	p1[3].draw();   // disaster
}
} // namespace ex_b

} // namespace ex4_array

namespace ex5_bitset
{

bitset<9> bs1{"110001111"};
bitset<9> bs2{0b1'1000'1111}; // binary literal using digit separators

bitset<9> bs3 = ~bs1;      // complement: bs3=="001110000"
bitset<9> bs4 = bs1 & bs3; // all zeros
bitset<9> bs5 = bs1 << 2;  // shift left: bs5 = "000111100"

void binary(int i)
{
	bitset<8 * sizeof(int)> b = 1;      // assume 8-bit byte
	std::cout << b.to_string() << '\n'; // write out the bits of i
	// prefer this
	std::cout << b << '\n'; // write out the bits of i
}
} // namespace ex5_bitset

namespace ex5_pair
{

struct Entry {
};

namespace ex_a
{

struct My_res {
	Entry *ptr;
	Error_code err;
};

My_res complex_search(std::vector<Entry> &v, const std::string &s)
{
	Entry *found = nullptr;
	Error_code err = Error_code::found;
	// ... search for s in v ...
	return {found, err};
}

void user(const std::string &s)
{
	My_res r = complex_search(entry_table, s); // search entry_table
	if (r.err != Error_code::good) {
		// ... handle error ...
	}
	// ... use r.ptr ...
}
} // namespace ex_a

namespace ex_b
{
pair<Entry *, Error_code> complex_search(std::vector<Entry> &v, const std::string &s)
{
	Entry *found = nullptr;
	Error_code err = Error_code::found;
	// ... search for s in v ...
	return {found, err};
}

void user(const std::string &s)
{
	// implementation names
	auto r = complex_search(entry_table, s); // search entry_table
	if (r.second != Error_code::good) {
		// ... handle error ...
	}
	// ... use r.first ...

	// prefer to use structured bindings
	auto [ptr, success] = complex_search(entry_table, s); // search entry_table
	if (success != Error_code::good) {
		// ... handle error ...
	}
	// .. use ptr ...
}

} // namespace ex_b

namespace ex_c
{
using std::ranges::equal_range;

struct Record {
	std::string name;
};
std::ostream &operator<<(std::ostream &os, const Record &r)
{
	return os << r.name;
}
auto less = [](const Record &r1, const Record &r2) { return r1.name < r2.name; }; // compare names
void f(const std::vector<Record> &v) // assume that v is sorted on its "name" field
{
	auto [first, last] = equal_range(v.begin(), v.end(), Record{"Reg"}, less);

	for (auto p = first; p != last; ++p) // print all equal records
		std::cout << *p;                 // assume that << is defined for Record
}
} // namespace ex_c

} // namespace ex5_pair

namespace ex6_tuple
{
using std::literals::operator""s;
using std::get;

tuple t0{};                                             // empty
tuple<std::string, int, double> t1{"Shark", 123, 3.14}; // the type is explicitly specified
auto t2 = make_tuple(
	std::string{"Herring"}, 10, 1.23); // the type is deduced to tuple<string, int, double>
tuple t3{"Cod"s, 20, 9.99};            // the type is deduced to tuple<string, int, double>

void f1()
{
	// access by index
	std::string fish = get<0>(t1); // get the first element: "Shark"
	int cout = get<1>(t1);         // get the second element: 123
	double price = get<2>(t1);     // get the third element: 3.14
}

void f2()
{
	// access by type (when uniquely defined)
	auto fish = get<std::string>(t1); // get the string: "SHark"
	auto count = get<int>(t1);        // get the int: 123
	auto price = get<double>(t1);     // get the double: 3.14
}

void f3()
{
	get<string>(t1) = "Tuna"; // write to the string
	get<int>(t1) = 7;         // write to the int
	get<double>(t1) = 312;    // write to the double
}

void f4()
{
	auto [fish, count, price] = t1;                            // tipically used for a function call
	std::cout << fish << ' ' << count << ' ' << price << '\n'; // read
	fish = "Sea Bass";                                         // write
}

// messy, but compile-time generic
template <std::size_t N = 0, typename... Ts> constexpr void print(tuple<Ts...> tup)
{
	if constexpr (N < sizeof...(Ts)) {   // not yet at the end?
		std::cout << get<N>(tup) << ' '; // print the Nth element
		print<N + 1>(tup);               // print the next element
	}
}


} // namespace ex6_tuple

namespace ex7_alternatives
{

namespace ex_a_variants
{

variant<std::string, Error_code> compose_message(std::istream &s)
{
	std::string mess;

	bool no_problems;
	int some_problem;
	// ... read form s and compose message ...

	if (no_problems) {
		return mess; // return a string
	}
	else
		return Error_code{some_problem}; // return an Error_code
}

int main()
{
	auto m = compose_message(std::cin);

	if (holds_alternative<std::string>(m)) {
		std::cout << get<std::string>(m) << '\n';
	}
	else {
		auto err = get<Error_code>(m);
		// ... handle error ...
	}
	return 0;
}

namespace ex_compiler
{
struct Expression {
};
struct Statement {
};
struct Declaration {
};
struct Type {
};
using Node = variant<Expression, Statement, Declaration, Type>;

void check_a(Node *p)
{
	if (holds_alternative<Expression>(*p)) {
		Expression &e = get<Expression>(*p);
		/// ...
	}
	else if (holds_alternative<Statement>(*p)) {
		Statement &s = get<Statement>(*p);
		// ...
	}
	// ... Declaration and Type ...
}

template <class... Ts> struct overloaded : Ts... { // variadic template
	using Ts::operator()...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // deduction guide

void check_b(Node *p)
{
	std::visit(overloaded{
				   [](Expression &e) { /* ... */ }, [](Statement &s) { /* ... */ },
				   // ... Declaration and Type ...
			   },
		*p);
}

} // namespace ex_compiler


} // namespace ex_a_variants

namespace ex_b_optional
{
optional<std::string> compose_message(std::istream &s)
{
	std::string mess;

	bool no_problems;
	// ... read from s and compose message ...

	if (no_problems)
		return mess;

	return {}; // the empty optional
}

int main()
{
	if (auto m = compose_message(std::cin))
		std::cout << *m; // note the dereference (*)
	else {
		// ... handle error ...
	}
	return 0;
}

int sum(optional<int> a, optional<int> b)
{
	int res = 0;
	if (a)
		res += *a;
	if (b)
		res += *b;

	// don't
	// return *a + *b; // asking for trouble

	return res;
}
int x = sum(17, 19); // 36
int y = sum(17, {}); // 17
int z = sum({}, {}); // 0

} // namespace ex_b_optional

namespace ex_c_any
{
any compose_message(std::istream &s)
{
	std::string mess;

	bool no_problems;
	std::string mess;
	int error_number;
	// ... read from s and compose message ...

	if (no_problems)
		return mess; // return a string
	else
		return error_number; // return an int
}

int main()
{

	auto m = compose_message(std::cin);

	/* implicit */
	std::string &s = any_cast<std::string &>(m); // bad_any_access

	/* valor temporário */
	const std::string &s = any_cast<std::string>(m); // bad_any_access

	std::cout << s;

	/* explícito */
	if (m.type() == typeid(std::string)) {
		std::string &s = any_cast<std::string &>(m); // Usar referência
	}
	else {
		throw std::bad_any_cast();
	}


	return 0;
}

} // namespace ex_c_any

} // namespace ex7_alternatives


int main()
{
}
