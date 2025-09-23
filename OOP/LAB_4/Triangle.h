#pragma once
#include "Angle.h"

class Triangle : public Angle {
private:
	int a, b, c;
public:
	Triangle(int a1, int b1, int c1, Angle& angle);
	bool existsBySides();   
	bool is90();
	double area();
	void print_T();
};

