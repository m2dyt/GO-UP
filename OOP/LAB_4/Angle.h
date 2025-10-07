#pragma once

class Angle {
protected:
	int degrees;
public:
	Angle(double deg = 0);
	int getDegrees();  
	void setDegrees(int deg);

	void normalize();
	double toRadians();
	void print_A();


	Angle operator+(Angle& other);
	Angle operator-(Angle& other);

};
