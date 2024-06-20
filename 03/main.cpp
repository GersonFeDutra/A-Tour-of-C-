#include <vector>
#include <iostream>


int sum(const std::vector<int> &v)
{
	int s = 0;
	for (const int i : v)
		s += i;
	return s;
}

int main(void)
{
	std::vector fib = {1, 2, 3, 5, 8, 13, 21};
	int x = sum(fib);
	// x becomes 53
	std::cout << "sum(fib(7)): " <<  x << '\n';
}
