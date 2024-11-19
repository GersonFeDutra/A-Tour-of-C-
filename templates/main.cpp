#include "vector.hpp"
#include <iostream>
#include <list>
#include <string>


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


int main(void)
{
	Vector<char> vc(200);           // vector of 200 characters
	Vector<std::string> vs(17);     // vector of 17 strings
	Vector<std::list<int>> vli(45); // vector of 45 lists of integers

	// init vectors

	// use vectors
	//write(vs);
    f2(vs);
}
