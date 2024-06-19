#include <iostream>

struct Vector {
	int sz;       // number of elements
	double *elem; // pointer to elements
};


void vector_init(Vector &v, int s)
{
	v.elem = new double[s]; // allocate an array of s doubles
	v.sz = s;
}

double read_and_sum(int s)
// read s integers from cin and return their sum; s is assumed to be positive
{
	Vector v;
	vector_init(v, s); // allocate s elements for v
	for (int i = 0; i != s; ++i)
		std::cin >> v.elem[i]; // read into elements
	double sum = 0;
	for (int i = 0; i != s; ++i)
		sum += v.elem[i]; // compute the sum of the elements
	return sum;
}

#include <random>
int main()
{
	int result = read_and_sum(std::rand() % 10);
	std::cout << "sum: " << result << '\n';
}
