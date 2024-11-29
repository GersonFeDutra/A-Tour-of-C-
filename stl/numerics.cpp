#include <cerrno>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <complex>
#include <execution>
#include <limits>
#include <numeric>
#include <random>
#include <valarray>

// utils
#include <iostream>
#include <vector>

using std::complex;
using std::numeric_limits;

using std::default_random_engine;
using std::uniform_int_distribution;

using std::valarray;

using std::reduce;

using std::int32_t, std::uint_least64_t;
using std::size_t;


namespace ex1
{

int main()
{
	errno = 0; // clear old error state


	double d = sqrt(-1);

	if (errno == EDOM)
		std::cerr << "sqrt() not defined for negative argument\n";


	errno = 0; // clear old error state

	double dd = pow(numeric_limits<double>::max(), 2);

	if (errno == ERANGE)
		std::cerr << "result of pow() too large to represent as a double\n";
}
} // namespace ex1


namespace ex2_parallel
{
using namespace std::execution;

int main()
{

	std::vector<double> v{1, 2, 3, 4, 5, 9999.99999};
	auto s = reduce(v.begin(), v.end()); // calculate the sum using a double as the accumulator

	std::vector<double> large;
	// ... fill large with lots of values ...

	auto s2 = reduce(
		par_unseq, large.begin(), large.end()); // calculate the sum using available parallelism

	return 0;
}

void f(complex<float> fl, complex<double> db)
{
	using namespace std; // help with deduction guides

	complex<long double> ld{fl + sqrt(db)};
	db += fl * 3.0f;
	fl = pow(1.0f / fl, 2);
	// ...
}

} // namespace ex2_parallel


namespace ex3_random
{

class Rand_int
{
public:
	Rand_int(int low, int high) : dist{low, high}
	{
	}
	int operator()()
	{
		return dist(re);
	} // draw an int
	void seed(int s)
	{
		re.seed(s);
	} // choose new random engine seed
private:
	default_random_engine re; // random engine
	uniform_int_distribution<> dist;
};


void f()
{
	using my_engine = default_random_engine;            // type of engine
	using my_distribution = uniform_int_distribution<>; // type of distribution

	my_engine eng{};                        // the default version of the engine
	my_distribution dist{1, 6};             // distribution that maps to the ints 1..6
	auto die = [&]() { return dist(eng); }; // make generator

	int x = die(); // roll the die: x becomes a value in [1:6]

	Rand_int rnd{1, 10}; // make a random number generator for [1:10]
	int x = rnd();       // x is a number in [1:10]
}

int main()
{
	constexpr int max = 9;
	Rand_int rnd{0, max}; // make a uniform random number generator

	std::vector<int> histogram(max + 1); // make a vector of appropriate size
	for (int i = 0; i != 200; ++i)
		++histogram[rnd()]; // fill histogram with the frequencies of numbers [0:max]

	for (int i = 0; i != histogram.size(); ++i) { // write out a bar graph
		std::cout << i << '\t';
		for (int j = 0; j != histogram[i]; ++j)
			std::cout << '*';
		std::cout << '\n';
	}

	return 0;
}

void g()
{
	// deterministic seeding
	Rand_int rnd{10, 20};
	for (int i = 0; i < 10; ++i)
		std::cout << rnd() << ' '; // 16 13 20 19 14 17 10 16 15 14

	rnd.seed(999);
	for (int i = 0; i < 10; ++i)
		std::cout << rnd() << ' '; // 11 17 14 19 20 13 20 14 16 19

	rnd.seed(999);
	for (int i = 0; i < 10; ++i)
		std::cout << rnd() << ' '; // 11 17 14 19 20 13 20 14 16 19
}

} // namespace ex3_random


namespace ex4_vector_arithmetic
{

void f(valarray<double> &a1, valarray<double> &a2)
{
	valarray<double> a = a1 * 3.14 + a2 / a1; // numeric array operators *, +, /, and =
	a2 += a1 * 3.14;
	a = abs(a);
	double d = a2[7];
	// ...
}

} // namespace ex4_vector_arithmetic


namespace ex5_math_constants
{

void area(float r)
{
	using namespace std::numbers; // this is where the mathematical constants are kept

	double d = pi * r * r;
	float f = pi_v * r * r;

	// ...
}

template <typename T> constexpr T tau_v = 2 * pi_v<T>;

constexpr double tau = tau_v<double>;

} // namespace ex5_math_constants


int main()
{
	ex1::main();

	// built-in properties
	static_assert(numeric_limits<char>::is_signed, "unsigned characters!");
	static_assert(100'000 < numeric_limits<int>::max(), "small ints!");
}
