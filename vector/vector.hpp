#pragma once
#include <initializer_list>

#ifdef DEBUG
#include <iostream>
#endif

class Vector
{
public:
	Vector(std::initializer_list<double>); // initialize with a list of doubles

	void push_back(double); // add element at end, increasing the size by one
	                        // ...

	Vector() {}                  // default constructor
	explicit Vector(int s);      // constructor: acquire resources

#ifdef DEBUG
	~Vector()
	{
		std::cerr << sz << " deleted\n";
		delete[] elem;
	}
#else
	~Vector() { delete[] elem; } // destructor: release resources
#endif

	Vector(const Vector&);            // copy constructor
	Vector& operator=(const Vector&); // copy assignment

	Vector(Vector&&);            // move constructor
	Vector& operator=(Vector&&); // move assignment

	double& operator[](int i);
	double& operator[](int i) const;
	int size() const;

private:
	double *elem = nullptr; // elem points to an array of sz doubles
	int sz = 0;
};
