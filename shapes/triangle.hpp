#pragma once
#include "shape.hpp"

class Triangle : public Shape
{
public:
	Triangle(Point p1, Point p2, Point p3); // constructor
	Point center() const override;
	void move(Point to) override;
	void draw() const override;
	void rotate(int) override
	{
	} // nice simple algorithm
private:
    Point p1, p2, p3;
};
