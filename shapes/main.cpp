#include "circle.hpp"
#include "shape.hpp"
#include "smiley.hpp"
#include "triangle.hpp"
#include <iostream>
#include <memory>
#include <vector>

enum class Kind { circle, triangle, smiley };
std::unique_ptr<Shape> read_shape(std::istream &is) // read shape descriptions from input stream is
{
	int r;
	Kind k;
	Point p, p1, p2, p3;
	Shape *e1, *e2, *m;
	// ... read shape header from is and find its Kind k ...
	switch (k) {
		case Kind::circle:
			// read circle data {Point,int} into p and r
			return std::unique_ptr<Shape>{new Circle{p, r}};
		case Kind::triangle:
			// read triangle data {Point,Point,Point} into p1, p2, and p3
			return std::unique_ptr<Shape>{new Triangle{p1, p2, p3}}; // §13.2.1
		case Kind::smiley:
			// read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1, e2, and m
			Smiley *ps = new Smiley{p, r};
			ps->add_eye(std::unique_ptr<Shape>(e1));
			ps->add_eye(std::unique_ptr<Shape>(e2));
			ps->set_mouth(std::unique_ptr<Shape>(m));
			return std::unique_ptr<Shape>{ps};
	}
}

void rotate_all(
	std::vector<std::unique_ptr<Shape>> &v, int angle) // rotate v’s elements by angle degrees
{
	for (auto &p : v)
		p->rotate(angle);
}


void draw_all(std::vector<std::unique_ptr<Shape>> &v) // draw v’s elements
{
	for (auto &p : v)
		p->draw();
}


void user()
{
	std::vector<std::unique_ptr<Shape>> v;
	while (std::cin)
		v.push_back(read_shape(std::cin));
	draw_all(v);       // call draw() for each element
	rotate_all(v, 45); // call rotate(45) for each element
} // all Shapes implicitly destroyed


/*
void old_user()
{
    // use shapes here
    Shape *ps{read_shape(std::cin)};
    if (Smiley *p = dynamic_cast<Smiley *>(ps)) { // ... does ps point to a Smiley? ...

    } // ... a Smiley; use it
    else {

    } // ... not a Smiley, try something else ...

    Shape *ps2{read_shape(std::cin)};
    Smiley &r{dynamic_cast<Smiley &>(*ps2)}; // somewhere, catch std::bad_cast
}
*/


void main()
{
	user();
}
