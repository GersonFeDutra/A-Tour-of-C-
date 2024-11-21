#include <iostream>
#include <string>


template <typename T>
concept Printable = requires(T t) { std::cout << t; }; // just one operation!

void print()
{
	// What we do for no arguments: nothing
}

template <Printable T, Printable... Tail> void print(T head, Tail... tail)
{
	std::cout << head << ' '; // first, what we do for the head
	print(tail...);
}


void user()
{
	using std::literals::string_literals::operator""s;

	print("first: ", 1, 2.2, "hello\n"s);
}

/* to disable the empty print case
template <Printable T, Printable... Tail> void print(T head, Tail... tail)
{
	cout << head << ' ';
	if constexpr (sizeof...(tail) > 0)
		print(tail...);
}
*/
