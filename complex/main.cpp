#include "complex.hpp"

void f(complex z)
{
	complex a{2.3}; // construct {2.3,0.0} from 2.3
	complex b{1 / a};
	complex c{a + z * complex{1, 2.3}};
	// ...
	if (c != b)
		c = -(b / a) + 2 * b;
}

#include <iostream>
int main()
{
	complex i = 1.0i;
	complex x(3.14, 1);
	x += i;
	std::cout << x.real << '+' << x.imag << 'i' << '\n';
}
