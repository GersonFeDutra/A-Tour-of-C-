#pragma once
struct Point {
	double x, y;
};

class Shape
{
public:
	virtual Point center() const = 0; // pure virtual
	virtual void move(Point to) = 0;
	virtual void draw() const = 0; // draw on current "Canvas"
	virtual void rotate(int angle) = 0;
	virtual ~Shape()
	{
	} // destructor
	Shape(const Shape &) = delete; // disable copy
	Shape &operator=(const Shape &) = delete;
	// ...
};
