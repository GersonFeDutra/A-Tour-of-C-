#include <iostream>
#include <string>

struct Node {
	//...
};

enum Type { ptr, num }; // a Type can hold values ptr and num (§2.5)

/*
struct Entry {
    std::string name; // str ing is a standard-librar y type
    Type t;
    Node *p; // use p if t==ptr
    int i;
    // use i if t==num
};
*/
union Value {
	Node *p;
	int i;
};
struct Entry {
	std::string name;
	Type t;
	Value v; // use v.p if t==ptr; use v.i if t==num
};


void f(Entry *pe)
{
	if (pe->t == num)
		// std::cout << pe->i;
		std::cout << pe->v.i;
	// ...
}
