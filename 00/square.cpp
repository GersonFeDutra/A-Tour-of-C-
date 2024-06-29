// include (‘‘import’’) the declarations for the I/O stream library
#include <iostream>

using namespace std;

double square(double x) // square a double precision floating-point number
{
	return x * x;
}

void print_square(double x)
{
	// make names from std visible without std:: (§3.4)
	cout << "the square of " << x << " is " << square(x) << "\n";
}

int main()
{
	print_square(1.234); // print: the square of 1.234 is 1.52276
}
