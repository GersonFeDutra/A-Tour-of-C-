module; // this compilation will define a module
        // ... here we put stuff that Vector might need for its implementation ...

export module Vector; // defining the module called "Vector"
#include <stdexcept>
#include <initializer_list>

export class Vector
{
public:
	Vector(std::initializer_list<double>); // initialize with a list of doubles
	// ...
	void push_back(double); // add element at end, increasing the size by one
	                        // ...

	explicit Vector(int s) : elem{new double[s]}, sz{s} // constructor: acquire resources
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
