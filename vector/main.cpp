#include <iostream>

class Vector
{
public:
	Vector(int s) : elem{new double[s]}, sz{s}
	{
	} // construct a Vector
	double &operator[](int i)
	{
		return elem[i];
	}
	int size()
	{
		return sz;
	}

private:
	double *elem; // pointer to the elements
	int sz;
	// the number of elements
	// element access: subscripting
};

double read_and_sum(int s)
{
	Vector v(s);
	for (int i = 0; i != v.size(); ++i)
		// make a vector of s elements
		std::cin >> v[i]; // read into elements
	double sum = 0;
	for (int i = 0; i != v.size(); ++i)
		sum += v[i]; // take the sum of the elements
	return sum;
}

#include <random>
int main()
{
	int result = read_and_sum(std::rand() % 10);
	std::cout << "sum: " << result << '\n';
}
