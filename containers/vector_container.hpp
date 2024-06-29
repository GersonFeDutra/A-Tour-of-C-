#pragma once
#include "container.hpp"
#include "vector.hpp"

class Vector_container : public Container
{ // Vector_container implements Container
public:
	Vector_container(int s) : v(s)
	{
	} // Vector of s elements
	~Vector_container()
	{
	}
	double &operator[](int i) override
	{
		return v[i];
	}
	int size() const override
	{
		return v.size();
	}

private:
	Vector v;
};
