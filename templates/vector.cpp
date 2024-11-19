#pragma once
#include <algorithm>

template <typename T> class Vector
{
private:
	T *elem; // elem points to an array of sz elements of type T
	int sz;

public:
	// constructor: establish invariant, acquire resources
	explicit Vector(int s);

	// destructor: release resources
	~Vector()
	{
		delete[] elem;
	}

public: // ... copy and move operations ...
	// copy
	Vector(const Vector &v) : elem{new T[v.sz]}, sz{v.sz}
	{
		std::copy(v.elem, v.elem + v.sz, elem);
	}

	// move
	Vector(Vector &&v) : elem{v.elem}, sz{v.sz}
	{
	}

	// move assignment
	Vector &operator=(Vector &&v)
	{
		delete[] elem;
		elem = v.elem;
		sz = v.sz;
		return *this;
	}

	// copy assignment
	Vector &operator=(const Vector &v)
	{
		sz = v.sz;
		elem = new T[v.sz];
		std::copy(v.elem, v.elem + v.sz, elem);
		return *this;
	}

	T &operator[](int i)
	{
		return elem[i];
	}

	const T &operator[](int i) const
	{
		return elem[i];
	}

	int size() const
	{
		return sz;
	}
};
