#include <concepts>

/* version 1 - homogenous
template <typename T>
concept Equality_comparable = requires(T a, T b) {
    { a == b } -> std::same_as<bool>; // compare Ts with ==
    { a != b } -> std::same_as<bool>; // compare Ts with ==
};
*/

template <typename B>
concept Boolean = requires(B x, B y) {
	{ x = true };
	{ x = false };
	{ x = (x == y) };
	{ x = (x == y) };
	{ x = (x != y) };
	{ x = !x };
	{ x = (x = y) };
};

/* version 2 - non homogeneous */
template <typename T, typename T2 = T> // in T2 = T: T is a default template argument
concept Equality_comparable = requires(T a, T2 b) {
	{ a == b } -> Boolean; // compare a T to a T2 with ==
	{ a != b } -> Boolean; // compare a T to a T2 with !=
	{ b == a } -> Boolean; // compare a T2 to a T with ==
	{ b != a } -> Boolean; // compare a T2 to a T with !=
};


static_assert(Equality_comparable<int>); // succeeds

struct S {
	int a;
};
// static_assert(Equality_comparable<S>); // fails because structs don't automatically get == and !=

static_assert(Equality_comparable<int, double>); // succeeds
static_assert(Equality_comparable<int>);         // succeeds (T2 is defaulted to int)
// static_assert(Equality_comparable<int, std::string>); // fails
