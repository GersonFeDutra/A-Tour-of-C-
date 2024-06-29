module; // this compilation will define a module
        // ... here we put stuff that Vector might need for its implementation ...

export module Vector; // defining the module called "Vector"
#include <stdexcept>

export class Vector
{
public:
	Vector(int s) : elem{new double[s]}, sz{s} // constructor: acquire resources
	{
		for (int i = 0; i != s; ++i) // initialize elements
			elem[i] = 0;
	}
	~Vector()
	{
		delete[] elem;
	} // destructor: release resources

	double &operator[](int i);
	int size() const;

private:
	double *elem; // elem points to an array of sz doubles
	int sz;
};

Vector::Vector(int s)
{
	if (s < 0)
		throw length_error{"Vector constructor: negative size"};
	elem = new double[s];
	sz = s;
}

double &Vector::operator[](int i)
{
	if (i < 0 || size() <= i)
		throw out_of_range{"Vector::operator[]"};
	return elem[i];
}


int Vector::size()
{
	return sz;
}
