// modules support is not complete
// module; // this compilation will define a module
//         // ... here we put stuff that Vector might need for its implementation ...
#include "vector.hpp"
#include <stdexcept>

//export module Vector; // defining the module called "Vector"
//export class Vector ...

Vector::Vector(int s) : elem{new double[s]}, sz{s}
{
	if (s < 0)
		throw std::length_error{"Vector constructor: negative size"};

	for (int i = 0; i != s; ++i) // initialize elements
		elem[i] = 0;
}

Vector::Vector(const Vector& a)        // copy constructor
	: elem{new double[a.sz]}, sz{a.sz} // allocate space for elements
{
	for (int i = 0; i != sz; i++)      // copy elements
		elem[i] = a.elem[i];
}

Vector& Vector::operator=(const Vector& a) // copy assignment
{
	double *p = new double[a.sz];
	for (int i = 0; i != a.sz; i++)
		p[i] = a.elem[i];

	delete[] elem; // delete old elements
	elem = p;
	sz = a.sz;

	return *this;
}


double& Vector::operator[](int i)
{
	if (i < 0 || size() <= i)
		throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}


double& Vector::operator[](int i) const
{
	if (i < 0 || size() <= i)
		throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}


int Vector::size() const
{
	return sz;
}


Vector::Vector(std::initializer_list<double> lst)
	: elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
	std::copy(lst.begin(), lst.end(), elem); // copy from lst into elem (§12.6)
}


void Vector::push_back(double v)
{
	double *new_elem = new double[sz + 1];
	double *p, *q;
	for (p = new_elem, q = elem; p < p + sz; p++, q++)
		*p = *q;
	*p = v;
	delete[] elem;
	elem = new_elem;
}


class Vector_size_mismatch : std::exception {};


Vector operator+(const Vector& a, const Vector&b)
{
	if (a.size() != b.size())
		throw Vector_size_mismatch{};

	Vector res(a.size());

	for (int i = 0; i != a.size(); ++i)
		res[i] = a[i] + b[i];

	return res;
}
