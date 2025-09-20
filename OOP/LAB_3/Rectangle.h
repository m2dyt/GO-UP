#pragma once
#include <iostream>

struct Point {
	double x, y;
	Point(double x_0 = 0, double y_0 = 0) : x(x_0), y(y_0) {}
};

class Rectangle {
private:
	Point A, B, C, D;
public:
	Rectangle();
	Rectangle(Point a, Point b, Point c, Point d);
	~Rectangle();

	double perimetr();

	bool operator>(Rectangle& other);
	bool operator<(Rectangle& other);
	bool operator==(Rectangle& other);

	friend Rectangle operator*(Rectangle& r1, Rectangle& r2);

	void print();
};