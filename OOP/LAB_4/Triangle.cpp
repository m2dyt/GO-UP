#include "Triangle.h"
#include <cmath>
#include <iostream>

Triangle::Triangle(int a1, int b1, int c1, Angle& angle)
	: a(a1), b(b1), c(c1), Angle(angle) {}

bool Triangle::existsBySides() {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

bool Triangle::is90() {
	return degrees == 90;
}

double Triangle::area() {
	return a * b * 0.5;
}

void Triangle::print_T() {
    std::cout << "Стороны a " << a << ", b " << b << ", c " << c << std::endl;
    std::cout << "Угол A: " << degrees << " градусов" << std::endl;

    if (!existsBySides()) {
        std::cout << "Треугольник не существует (по сторонам)." << std::endl;
        return;
    }

    std::cout << "Треугольник существует." << std::endl;

    if (!is90()) {
        std::cout << " Это не прямоугольный треугольник." << std::endl;
        return;
    }
   
    std::cout << "Это прямоугольный треугольник." << std::endl;
    std::cout << "Площадь " << area() << std::endl;

    
}