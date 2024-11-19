#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>


void write(const Vector<std::string> &vs)
{
	for (int i = 0; i != vs.size(); ++i)
		std::cout << vs[i] << '\n';
}

void f2(Vector<std::string> &vs) // Vector of some strings
{
	for (auto &s : vs)
		std::cout << s << '\n';
}


template <typename T> using space_vector = std::vector<T, 3>;

template <class T> constexpr T viscosity = 0.4;
template <class T> constexpr space_vector<T> external_acceleration = {T{}, T{-9.8}, T{}};
auto vis2 = 2 * viscosity<double>;
auto acc = external_acceleration<float>;


template <typename T, typename T2>
constexpr bool Assignable = std::is_assignable<T &, T2>::value; // is_assignable is a type trait

template <typename T> void testing()
{
	static_assert(Assignable<T &, double>, "can't assign a double");
	static_assert(Assignable<T &, string>, "can't assign a string");
}


int main(void)
{
	Vector<char> vc(200);           // vector of 200 characters
	Vector<std::string> vs(17);     // vector of 17 strings
	Vector<std::list<int>> vli(45); // vector of 45 lists of integers

	// init vectors

	// use vectors
	// write(vs);
	f2(vs);

	testing<bool>();
	testing<const char *>();
}
