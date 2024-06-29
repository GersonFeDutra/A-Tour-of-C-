#include "circle.hpp"
#include "shape.hpp"
#include "smiley.hpp"
#include "triangle.hpp"
#include <iostream>
#include <vector>

enum class Kind { circle, triangle, smiley };
Shape *read_shape(std::istream &is) // read shape descriptions from input stream is
{
	int r;
	Kind k;
	Point p, p1, p2, p3;
	Shape *e1, *e2, *m;
	// ... read shape header from is and find its Kind k ...
	switch (k) {
		case Kind::circle:
			// read circle data {Point,int} into p and r
			return new Circle{p, r};
		case Kind::triangle:
			// read triangle data {Point,Point,Point} into p1, p2, and p3
			return new Triangle{p1, p2, p3};
		case Kind::smiley:
			// read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1, e2, and m
			Smiley *ps = new Smiley{p, r};
			ps->add_eye(e1);
			ps->add_eye(e2);
			ps->set_mouth(m);
			return ps;
	}
}

void rotate_all(std::vector<Shape *> &v, int angle) // rotate v’s elements by angle degrees
{
	for (auto p : v)
		p->rotate(angle);
}


void draw_all(std::vector<Shape *> &v) // draw v’s elements
{
	for (auto p : v)
		p->draw();
}

void main()
{
	// use shapes here
	std::vector<Shape *> v;
	while (std::cin)
		v.push_back(read_shape(std::cin));
	draw_all(v);       // call draw() for each element
	rotate_all(v, 45); // call rotate(45) for each element
	for (auto p : v)   // remember to delete elements
		delete p;
}
