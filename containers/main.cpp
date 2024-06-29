#include "list_container.hpp"
#include "vector_container.hpp"
#include <iostream>


void use(Container &c)
{
	const int sz = c.size();
	for (int i = 0; i != sz; ++i)
		std::cout << c[i] << '\n';
}

void g()
{
	Vector_container vc{10};
	use(vc);
}

void h()
{
	List_container lc = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	use(lc);
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
