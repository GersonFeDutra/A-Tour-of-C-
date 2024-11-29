#include <bit>
#include <chrono>
#include <functional>
#include <limits>
#include <source_location>
#include <type_traits>
#include <utility>
// others
#include <algorithm>
#include <format>
#include <iostream>
#include <memory>
#include <ranges>
#include <thread>
#include <vector>
#include <string>


constexpr bool is_unix()
{
#if defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
	return true;
#else
	return false;
#endif
}

namespace ex1_chrono
{
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace std::literals;
using namespace std::literals::chrono_literals;

void do_work()
{
	std::this_thread::sleep_for(10ms + 33us) // wait for 10 miliseconds and 33 microseconds
}

int main()
{
	using std::cout, std::format;

	// clocks
	auto t0 = system_clock::now();
	do_work();
	auto t1 = system_clock::now();

	cout << t1 - t0 << '\n'; // default unit: 20223[1/10000000]s
	cout << duration_cast<milliseconds>(t1 - t0).count() << "ms\n"; // specify unit: 2ms
	cout << duration_cast<nanoseconds>(t1 - t0).count() << "ns\n";  // specify unit: 2022300ns

	// calendar
	auto spring_day = April / 7 / 2018;
	cout << weekday(spring_day) << '\n';            // Sat
	cout << format("{:%A}\n", weekday(spring_day)); // Saturday

	auto spring_day2 = 2018y / April / 7; // alternative

	auto bad_day = 0d / January / 2024y;
	if (!bad_day.ok())
		cout << bad_day << " is not a valid day\n";

	sys_days t = sys_days{25y / February / 2022y}; // get a time point with the precision of days
	t += days{7};                                  // one week after February 25, 2022
	auto d = year_month_day{t};                    // convert the time point back to calendar

	cout << d << '\n';                                             // 2022-03-04
	cout << format("{:%B}/{}/{}\n", d.month(), d.day(), d.year()); // March/4/2022

	static_assert(weekday(April / 7 / 2018) == Saturday); // true

	// time zones
	auto tp = system_clock::now(); // tp is a time_point
	cout << tp << '\n';            // 2021-11-27 21:36:08.2085095

	zoned_time ztp{current_zone(), tp}; // 2021-11-27 16:36:08.2085095 EST
	cout << ztp << '\n';

	const time_zone est{"Europe/Copenhagen"};
	std::cout << zoned_time{&est, tp} << '\n'; // 2021-11-27 22:36:08.2085095 GMT+1

	return 0;
}


} // namespace ex1_chrono


namespace ex2_function_adaption
{
using std::conditional_t;
using std::enable_if;
using std::function;
using std::invoke_result_t;
using std::is_arithmetic_v;
using std::is_class_v, std::is_union_v;
using std::is_trivially_copyable_v;
using std::numeric_limits;

struct Shape {
	void draw();
};

using X = int;
void draw_all(std::vector<Shape *> &v)
{
	std::ranges::for_each(v, [](Shape *p) { p->draw(); });

	// using mem_fn
	std::ranges::for_each(v, std::mem_fn(&Shape::draw));

	// function
	int f1(double);                // defined elsewhere
	function<int(double)> f2 = f1; // initialize to f1

	int f2(std::string);
	function fct2{f2}; // fct2's type is function<int(string)>

	function fct3 = [](Shape *p) { p->draw(); }; // fct3's type is function<void(Shape *)>

	// type functions
	constexpr float min = numeric_limits<float>::min(); // smallest positive float
	constexpr int szi = sizeof(int);                    // size of int

	bool b = is_arithmetic_v<X>;               // true if X is one of the (built-in arithmetic types
	using Res = invoke_result_t<decltype(f1)>; // int if f is a function that returns an int

	template <typename T> using Store = conditional_t(sizeof(T) < max, On_stack<T>, On_heap<T>);
}

namespace type_functions
{

template <typename F, typename... Args> auto call(F f, Args... a, Allocator alloc)
{
	if constexpr (std::invocable<F, alloc, Args...>) // needs an allocator?
		return f(f, alloc, a...);
	else
		return f(f, a...);
}

template <typename Scalar> class complex
{
	Scalar re, im;

public:
	// constrain argument types  (using assert)
	static_assert(is_arithmetic_v<Scalar>, "Sorry, I support only complex of arithmetic types");
	// ...
};

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic Scalar> // constrains argument types (using concepts)
class complex
{
	Scalar re, im;

public:
	// ...
};

namespace ex_a
{

template <typename T, typename U>
concept Number = std::is_arithmetic_v<T> && std::is_arithmetic_v<U>;

// concept based on type trait 'Number'
template <typename T, typename U = T>
concept Arithmetic = Number<T, U> && Number<U, T>;

} // namespace ex_a

template <class T> void cpy1(T *first, T *last, T *target)
{
	if constexpr (is_trivially_copyable_v<T>)
		memcpy(first, target, (last - first) * sizeof(T));
	else
		while (first != last)
			*target++ = *first++;
}

} // namespace type_functions


namespace conditional_properties
{
template <typename T> class Smart_pointer
{
	// ...
	T &operator*() const;
	// T *operator->() const; // -> should work if and only if T is a class
	T *operator->() const
		requires is_class_v<T>; // -> is defined if and only if T is a class
};

template <typename T> Smart_pointer<std::vector<T>> v;

namespace ex_b
{
template <typename T>
concept Class = is_class_v<T> || is_union_v<T>; // unions are classes

template <Class T> class Smart_pointer
{
	// ...
	T &operator*() const;
	T *operator->() const
		requires Class<T>; // -> is defined if and only if T is a class or a union
};

} // namespace ex_b

} // namespace conditional_properties

namespace type_generators
{

template <typename T> class Smart_pointer
{
	// ...
	T &operator*();
	enable_if<is_class_v<T>, T &> operator->(); // -> is defined if and only if T is a class
	                                            // SFINAE: Substitution Failure Is Not An Error
};

} // namespace type_generators

} // namespace ex2_function_adaption


namespace ex3_source_location
{
using std::source_location;
// older versions < C++ 20 uses macros __FILE__, __LINE__, __COUNTER__

const source_location loc = source_location::current();

void log(const std::string &mes = "", const source_location &loc = source_location::current())
{
	if constexpr (is_unix())
		std::cout << "\33[33m";

	std::cout << loc.file_name() << '(' << loc.line() << ':' << loc.column() << ") " << mes << '\n';

	if constexpr (is_unix())
		std::cout << "\33[m";
}

void foo()
{
	log("Hello"); // ex: my_file.cpp (17, 4) foo: Hello

	// ...
}

int bar(const std::string &label)
{
	log(label); // ex: my_file.cpp (23, 4) bar: <<the value of label>>

	// ...
}

} // namespace ex3_source_location


namespace ex4_move_forward
{
using std::forward;
using std::move;

void f1()
{
	auto p = std::make_unique<int>(2);
	auto q = p;       // error: we can't copy a unique_ptr
	auto q = move(p); // p now holds nullptr

	// ...
}

template <typename T> void swap(T &a, T &b)
{
	T tmp{move(a)}; // the T constructor sees an rvalue and moves
	a = move(b);    // The T assignment sees an rvalue and moves
	b = move(tmp);  // the T assignment sees an rvalue and moves
}

int main()
{
	std::string s1 = "Hello";
	std::string s2 = "World";
	std::vector<std::string> v;

	v.push_back(s1);       // use a "const string&" argument; push_back() will copy
	v.push_back(move(s2)); // use a move constructor
	v.emplace_back(s1);    // an alternative; place a copy of s1 in a new end position of v

	std::cout << s1[2]; // write 'l'
	std::cout << s2[2]; // crash? // (generally) unspecified behavior

	return 0;
}

template <typename T, typename... Args> std::unique_ptr<T> make_unique(Args &&...args)
{
	return unique_ptr<T>{new T{std::forward<Args>(args)...}}; // forward each argument
}

} // namespace ex4_move_forward


namespace ex4_bit_manipulation
{
using std::bit_cast;
using std::bit_width;
using std::popcount;
using std::rotl;

int main()
{
	double val = 7.2;
	auto x = bit_cast<uint64_t>(val); // get the bit representation of a 64-bit floating point number
	auto y = bit_cast<unit64_t>(&val); // get the bit representation of a 64-bit pointer

	struct Word {
		std::byte b[8];
	};
	std::byte buffer[1024];
	// ...
	auto p = bit_cast<Word *>(&buffer[0]); // p points to 8 bytes
	auto i = bit_cast<int64_t>(*p);        // convert those 8 bytes to an integer
}

void use(unsigned int ui)
{
	int x0 = bit_width(ui);         // the smallest number of bits needed to represent ui
	unsigned int ui2 = rotl(ui, 8); // rotate left 8 bits (note: doesn't change ui)
	int x1 = popcount(ui);          // the number of 1s in ui
	                                // ...
}

} // namespace ex4_bit_manipulation

int main()
{
	int ext = ex1_chrono::main();

	// terminations
	exit(ext); // exit the process
	// calls the primitive atexit to destroy the program
	abort(); // exit the program immediately and unconditionally
	quick_exit(
		ext); // calls functions registered with at_quick_exit(); then terminate with return value x
	terminate(); // call default terminate_handler (abort)
}
