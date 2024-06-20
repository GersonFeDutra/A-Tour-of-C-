import Vector; //get Vector’s interface
#include <cmath>  // get the standard-library math function interface including sqrt()
#include <iostream>


// get the standard-librar y math function interface including sqrt()
double sqrt_sum(Vector &v)
{
	double sum = 0;
	for (int i = 0; i != v.size(); ++i)
		sum += std::sqrt(v[i]);
	return sum;
}


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
