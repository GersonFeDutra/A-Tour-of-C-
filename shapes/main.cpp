#include "circle.hpp"
#include "shape.hpp"
#include <vector>

void rotate_all(std::vector<Shape *> &v, int angle) // rotate v’s elements by angle degrees
{
	for (auto p : v)
		p->rotate(angle);
}

void main()
{
	// use shapes here
}
