#include "Angle.h"
#include <iostream>

void Angle::normalize() {
	degrees = degrees % 360;
}

Angle::Angle(double deg) : degrees(deg) {
	normalize();
}

double Angle::toRadians() {
	double PI = 3.14159265358979323846;
	return degrees * PI / 180;
}

int Angle::getDegrees() {
	return degrees;
}

void Angle::setDegrees(int deg) {
	degrees = deg;
	normalize();
}

void Angle::print_A(){
	std::cout << "”гол: " << degrees << " градусов, "
		<< toRadians() << " радиан" << std::endl;
}

Angle Angle::operator+(Angle& other) {
	return Angle(this->degrees + other.degrees);
}

Angle Angle::operator-(Angle& other) {
	return Angle(this->degrees - other.degrees);
}