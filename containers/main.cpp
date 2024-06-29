#include <iostream>
#include <vector_container.hpp>


void use(Container &c)
{
	const int sz = c.size();
	for (int i = 0; i != sz; ++i)
		std::cout << c[i] << '\n';
}


int main(void)
{
	// use containers

	// error : there can be no objects of an abstract class
	// Container c;

	// OK: Container is an interface
	Container *p = new Vector_container(10);

	use(*p);
}
