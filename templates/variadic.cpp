#include <iostream>
#include <string>


template <typename T>
concept Printable = requires(T t) { std::cout << t; }; // just one operation!

/*
void print()
{
	// What we do for no arguments: nothing
}

template <Printable T, Printable... Tail> void print(T head, Tail... tail)
{
	std::cout << head << ' '; // first, what we do for the head
	print(tail...);
}
*/

template<Printable ...T>
void print(T&&... args)
{
    (std::cout << ... << args) << '\n'; // print all the arguments
}


void user()
{
	using std::literals::string_literals::operator""s;

	//print("first: ", 1, 2.2, "hello\n"s);
    
    print("Hello!"s, ' ', "World!", ' ', 2017); // line ended in the print itself
}

/* to disable the empty print case
template <Printable T, Printable... Tail> void print(T head, Tail... tail)
{
    cout << head << ' ';
    if constexpr (sizeof...(tail) > 0)
        print(tail...);
}
*/

template <typename T, typename U = T>
concept Number = requires(T x, U y) {
	x += y;
	x -= y;
	x *= y;
	x /= y;
	x %= y;
	x + y;
	x - y;
	x *y;
	x / y;
	x % y;
	x = x;
	x = y; // copy
	x = 0;
};

template <Number... T> int sum(T... v)
{
	return (v + ... + 0); // Add all elements of v starting with 0
}

/*
template <Number... T> int sum(T... v)
{
    // left folded
	return (0 + ... + v); // Add all elements of v starting with 0
}
*/
