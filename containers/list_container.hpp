#pragma once
#include "container.hpp"
#include <initializer_list>
#include <list>
#include <stdexcept>

class List_container : public Container
{ // List_container implements Container
public:
	List_container()
	{
	} // empty List
	List_container(std::initializer_list<double> il) : ld{il}
	{
	}
	~List_container()
	{
	}
	double &operator[](int i) override;
	int size() const override
	{
		return ld.size();
	}

private:
	std::list<double> ld; // (standard-librar y) list of doubles (§11.3)
};

double &List_container::operator[](int i)
{
	for (auto &x : ld) {
		if (i == 0)
			return x;
		--i;
	}
	throw std::out_of_range{"List container"};
}
