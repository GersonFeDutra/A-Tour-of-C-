class complex
{
public:
	double real, imag; // representation: two doubles
public:
	complex(double r, double i) : real{r}, imag{i}
	// construct complex from two scalars
	{
	}

	complex(double r) : real{r}, imag{0}
	// construct complex from one scalar
	{
	}

	complex() : real{0}, imag{0}
	// default complex: {0,0}
	{
	}

	complex &operator+=(complex z)
	{
		real += z.real; // add to real and imag
		imag += z.imag;
		return *this; // and return the result
	}

	complex &operator-=(complex z)
	{
		real -= z.real;
		imag -= z.imag;
		return *this;
	}

	// defined out-of-class somewhere
	complex &operator*=(complex);
	complex &operator/=(complex);
};

/* Many useful operations do not require direct access to the representation of
complex, so they can be defined separately from the class definition: */
complex operator+(complex a, complex b)
{
	return a += b;
}
complex operator-(complex a, complex b)
{
	return a -= b;
}
complex operator-(complex a)
{
	return {-a.real, -a.imag};
} // unary minus
complex operator*(complex a, complex b)
{
	return a *= b;
}
complex operator/(complex a, complex b)
{
	return a /= b;
}
/* Here, I use the fact that an argument passed by value is copied so that I can
modify an argument without affecting the caller’s copy and use the result as
the return value */

bool operator==(complex a, complex b) // equal
{
	return a.real == b.real && a.imag == b.imag;
}
bool operator!=(complex a, complex b) // not equal
{
	return !(a == b);
}
complex sqrt(complex); // the definition is elsewhere

void f(complex z)
{
	complex a{2.3}; // construct {2.3,0.0} from 2.3
	complex b{1 / a};
	complex c{a + z * complex{1, 2.3}};
	// ...
	if (c != b)
		c = -(b / a) + 2 * b;
}

#include <iostream>
int main()
{
	complex i(0, 1);
	complex x(3.14, 1);
	x += i;
	std::cout << x.real << '+' << x.imag << 'i' << '\n';
}
