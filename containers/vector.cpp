#include "vector.hpp"
#include <algorithm>
#include <stdexcept>

Vector::Vector(int s)
{
	if (s < 0)
		throw std::length_error{"Vector constructor: negative size"};
	elem = new double[s];
	sz = s;
}

double &Vector::operator[](int i)
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
