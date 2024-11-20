#include <concepts>
#include <iterator>
#include <type_traits>

template <typename S> using Value_type = typename S::value_type;
template <typename S> using Iterator_type = decltype(std::begin(std::declval<S &>()));

template <typename S>
concept Sequence = requires(S a) {
	typename Value_type<S>;                         // S must have a value type.
	typename Iterator_type<S>;                      // S must have an iterator type.
	{ begin(a) } -> std::same_as<Iterator_type<S>>; // begin(a) must return an iterator
	{ end(a) } -> std::same_as<Iterator_type<S>>;   // end(a) must return an iterator
	requires std::same_as<Value_type<S>, Value_type<Iterator_type<S>>>;
	requires std::input_iterator<Iterator_type<S>>;
};

template <typename A, typename B = A>
concept Arithmetic = requires(A a, B b) {
	{ a += b };
	{ a -= b };
	{ a *= b };
	{ a /= b };
	{ a %= b };
	{ a + b };
	{ a - b };
	{ a *b };
	{ a / b };
	{ a % b };
};

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
    requires Arithmetic<Value_type<Seq>, Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}
*/

/* version 2 - verbose
template<typename Seq, typename Num>
    requires Sequence<Seq> && Number<Num> && Arithmetic<Value_type<Seq>, Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}
*/


/* version 2 - compact */
template <Sequence Seq, Arithmetic<Value_type<Seq>> Num>
	requires Arithmetic<Value_type<Seq>, Num>
Num sum(Seq s, Num v)
{
	for (const auto &x : s)
		v += x;
	return v;
}
