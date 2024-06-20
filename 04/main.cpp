#include <stdlib.h>
#include <assert.h>
#include <iostream>

class Matrix
{
private:
	double *data;
	size_t m, n;

public:
	Matrix(size_t m, size_t n) : data{new double[m * n]}, m{m}, n{n} {
		for (size_t i = 0; i < m * n; ++i)
			*(data + i) = i;
	}

	Matrix operator+(const Matrix &x)
	{
		const Matrix &y = *this;
		assert(x.m == y.m && x.n == x.n);

		Matrix res(x.m, x.n);
		// ... for all res[i,j], res[i,j] = x[i,j]+y[i,j] ...
		for (double *p = x.data, *q = y.data, *r = res.data;
				p < x.data + (x.m * x.n);
				p++, q++, r++)
			*r = *p + *q;

		return res;
	}

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};


std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	os << '[' << '\n';
	for (size_t i = 0; i < mat.m; ++i) {
		for (size_t j = 0; j < mat.n; ++j)
			os << ' ' << *(mat.data + mat.m * i + j);
		os << '\n';
	}
	os << ']';

    return os;
}


int main(void)
{
	Matrix m1(2, 2), m2(2, 2);
	std::cout << m1 << " + " << m2;
	// ...
	Matrix m3 = m1 + m2;
	std::cout << " = " << m3 << '\n';
	// no copy
}
