#include <iostream>
#include <string>
#include <variant>

struct Node {
	//...
};


struct Entry {
	std::string name;
	std::variant<Node *, int> v;
};

void f(Entry *pe)
{
	if (std::holds_alternative<int>(pe->v)) // does *pe hold an int? (see §13.5.1)
		std::cout << std::get<int>(pe->v);
	// ...
}
