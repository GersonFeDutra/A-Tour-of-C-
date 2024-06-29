#pragma once
#include "circle.hpp"
#include <memory>
#include <vector>

class Smiley : public Circle
{ // use the circle as the base for a face
public:
	Smiley(Point p, int rad) : Circle{p, rad}, mouth{nullptr}
	{
	}
	// ~Smiley(); // no destructor needed with unique_ptr
	void move(Point to) override;
	void draw() const override;
	void rotate(int) override;
	void add_eye(std::unique_ptr<Shape> s)
	{
		eyes.push_back(s);
	}
	void set_mouth(std::unique_ptr<Shape> s);
	virtual void wink(int i); // wink eye number i

	// ...
private:
	std::vector<std::unique_ptr<Shape>> eyes; // usually two eyes
	std::unique_ptr<Shape> mouth;
};
