#pragma once
#include <algorithm>
#include <exception>

template <typename T> class Vector
{
private:
	T *elem; // elem points to an array of sz elements of type T
	int sz;

public:
	// constructor: establish invariant, acquire resources
	explicit Vector(std::size_t s);

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

	T &operator[](std::size_t i);

	const T &operator[](std::size_t i) const;

	int size() const
	{
		return sz;
	}
};


template <typename T> Vector<T>::Vector(std::size_t s)
{
	elem = new T[s];
	sz = s;
}


template <typename T> T &Vector<T>::operator[](std::size_t i)
{
	if (i >= size())
		throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}


template <typename T> const T &Vector<T>::operator[](std::size_t i) const
{
	if (i >= size())
		throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}

template <typename T> T* begin(Vector<T> &x)
{
	return x.size() ? &x[0] : nullptr;
}

template <typename T> T* end(Vector<T> &x)
{
	// pointer to first element or nullptr
	return x.size() ? &x[0] + x.size() : nullptr;
}
