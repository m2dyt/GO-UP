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
    std::cout << "������� a " << a << ", b " << b << ", c " << c << std::endl;
    std::cout << "���� A: " << degrees << " ��������" << std::endl;

    if (!existsBySides()) {
        std::cout << "����������� �� ���������� (�� ��������)." << std::endl;
        return;
    }

    std::cout << "����������� ����������." << std::endl;

    if (!is90()) {
        std::cout << " ��� �� ������������� �����������." << std::endl;
        return;
    }
   
    std::cout << "��� ������������� �����������." << std::endl;
    std::cout << "������� " << area() << std::endl;

    
}