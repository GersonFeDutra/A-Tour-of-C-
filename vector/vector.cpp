module; // this compilation will define a module
        // ... here we put stuff that Vector might need for its implementation ...

#include <stdexcept>
#include <initializer_list>

export module Vector; // defining the module called "Vector"

export class Vector
{
public:
	Vector(std::initializer_list<double>); // initialize with a list of doubles

	void push_back(double); // add element at end, increasing the size by one
	                        // ...

	Vector() {}                  // default constructor
	explicit Vector(int s);      // constructor: acquire resources
	~Vector() { delete[] elem; } // destructor: release resources

	Vector(const Vector&);            // copy constructor
	Vector& operator=(const Vector&); // copy assignment

	double &operator[](int i);
	int size() const;

private:
	double *elem = nullptr; // elem points to an array of sz doubles
	int sz = 0;
};

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
