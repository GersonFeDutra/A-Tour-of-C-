#include <complex>
#include <list>
#include <vector>

template <typename Sequence, typename Value> Value sum(const Sequence &s, Value v)
{
	for (auto x : s)
		v += x;
	return v;
}

void user(std::vector<int> &vi, std::list<double> &ld, std::vector<std::complex<double>> &vc)
{
	int x = sum(vi, 0);                       // the sum of a vector of ints (add ints)
	double d = sum(vi, 0.0);                  // the sum of a vector of ints (add doubles)
	double dd = sum(ld, 0.0);                 // the sum of a list of doubles
	auto z = sum(vc, std::complex{0.0, 0.0}); // the sum of a vector of complex<double>s
}
