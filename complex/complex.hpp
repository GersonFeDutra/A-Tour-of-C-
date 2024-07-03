class complex
{
public:
    // representation: two doubles with default value 0.0
	double real = 0;
    double imag = 0;
public:
	// construct complex from two scalars : {r,i}
	complex(double r, double i) : real{r}, imag{i} {}

    // construct complex from one scalar : {r,0}
	complex(double r) : real{r} {}

	// default complex : {0,0}
	complex() {}

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
