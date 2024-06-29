#pragma once
#include <initializer_list>

class Vector
{
public:
	Vector(std::initializer_list<double>); // initialize with a list of doubles
	// ...
	void push_back(double); // add element at end, increasing the size by one
	                        // ...

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
