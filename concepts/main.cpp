#include <concepts>
#include <iterator>
#include <list>
#include <ranges>
#include <type_traits>
#include <vector>

template <typename T, typename U = T>
concept Number = requires(T x, U y) {
	x += y;
	x -= y;
	x *= y;
	x /= y;
	x %= y;
	x + y;
	x - y;
	x *y;
	x / y;
	x % y;
	x = x;
	x = y; // copy
	x = 0;
};

template <typename T, typename U = T>
concept Arithmetic = Number<T, U> && Number<U, T>;

template <class S> using Value_type = typename S::value_type;

/* our definition
template <typename S>
concept Sequence = requires(S a) {
    typename std::ranges::range_value_t<S>; // S must have a value type.
    typename std::ranges::iterator_t<S>;    // S must have an iterator type.

    { a.begin() } -> std::same_as<std::ranges::iterator_t<S>>; // begin(a) must return an iterator
    { a.end() } -> std::same_as<std::ranges::iterator_t<S>>;   // end(a) must return an iterator

    requires std::input_iterator<std::ranges::iterator_t<S>>; // S's iterator must be an
    // input_iterator
    requires std::same_as<std::ranges::range_value_t<S>, std::iter_value_t<S>>;
};
*/
/* stl definition */
template <typename S>
concept Sequence = std::ranges::input_range<S>; // simple to write and general

/* version 1
template<typename Seq, typename Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}
*/

/* version 2
template<Sequence Seq, Number Num>
    requires Arithmetic<std::ranges::range_value_t<Seq>, Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}
*/

/* version 2 - verbose
template<typename Seq, typename Num>
    requires Sequence<Seq> && Number<Num> && Arithmetic<std::ranges::range_value_t<Seq>, Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}
*/


/* version 2 - compact */
template <Sequence Seq, Arithmetic<std::ranges::range_value_t<Seq>> Num> Num sum(Seq s, Num v)
{
	for (const auto &x : s)
		v += x;
	return v;
}

double sum(const std::vector<int> &v)
{
	double res = 0;
	for (auto x : v)
		res += x;
	return res;
}

template <typename Iter, typename Val> Val accumulate(Iter first, Iter last, Val res)
{
	for (auto p = first; p != last; ++p)
		res += *p;
	return res;
}


template <std::forward_iterator Iter, Arithmetic<std::iter_value_t<Iter>> Val>
Val accumulate(Iter first, Iter last, Val res)
{
	for (auto p = first; p != last; ++p)
		res += *p;

	return res;
}


void use(const std::vector<int> &vec, const std::list<double> &lst)
{
	auto sum = accumulate(vec.begin(), vec.end(), 0.0); // accumulate in a double
	auto sum2 = accumulate(lst.begin(), lst.end(), sum);
}

template<std::ranges::forward_range R, Arithmetic<std::ranges::range_value_t<R>> Val>
Val accumulate(const R& r, Val res = 0)
{
	for (auto x : r)
		res += x;
	return res
}


int main(void)
{
	std::vector v = {1, 2, 3, 4};
	std::list l = {1.0, 2.0, 3.0};
	use(v, l);
}
