#include <iostream>
#include "Rectangle.h"
#include <cmath>

Rectangle::Rectangle() : A(0,0), B(0, 0), C(0, 0), D(0, 0) {}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : A(a), B(b), C(c), D(d) {}

Rectangle::~Rectangle() {}


double distanse(Point& p1, Point& p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double Rectangle::perimetr() {
	double ab = distanse(A, B);
	double bc = distanse(B, C);
	double cd = distanse(C, D);
	double da = distanse(D, A);
	return ab + bc + cd + da;
}

bool Rectangle::operator<(Rectangle& other) {
	return this->perimetr() < other.perimetr();
}

bool Rectangle::operator>(Rectangle& other) {
	return this->perimetr() > other.perimetr();
}

bool Rectangle::operator==(Rectangle& other) {
	return (this->perimetr() - other.perimetr()) < 1e-6;
}

Rectangle operator*(Rectangle& r1, Rectangle& r2) {
	double minX = std::min({ r1.A.x, r1.B.x, r1.C.x, r1.D.x, r2.A.x, r2.B.x, r2.C.x, r2.D.x });
	double minY = std::min({ r1.A.y, r1.B.y, r1.C.y, r1.D.y, r2.A.y, r2.B.y, r2.C.y, r2.D.y });
	double maxX = std::max({ r1.A.x, r1.B.x, r1.C.x, r1.D.x, r2.A.x, r2.B.x, r2.C.x, r2.D.x });
	double maxY = std::max({ r1.A.y, r1.B.y, r1.C.y, r1.D.y, r2.A.y, r2.B.y, r2.C.y, r2.D.y });
	return Rectangle(Point(minX, minY), Point(maxX, minY), Point(maxX, maxY), Point(minX, maxY));
}

void Rectangle::print() {
	std::cout << "Rectangle (" << A.x << ", " << A.y << ") "
	<< "(" << B.x << ", " << B.y << ") "
	<< "(" << C.x << ", " << C.y << ") "
	<< "(" << D.x << ", " << D.y << ")" << std::endl;
}
