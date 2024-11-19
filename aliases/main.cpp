#include <list>
#include <vector>
#include <string>

using size_t = unsigned int;

template <typename T> class Vector
{
public:
	using value_type T; // alias for a template instance
	                    // ...
};

template <typename C> using Value_type = typename C::value_type; // the type of C's elements

template <typename Container> void algo(Container &c)
{
	std::vector<Value_type<Container>> vec; // keep results here
}

template <typename Key, typename Value> class Map
{
	// ...
};
template <typename Value> using String_map = Map<std::string, Value>;
String_map<int> m;
// m is a Map<str ing,int>


int main(void)
{
	std::list<int> l{1, 2};

	algo(l);
}
