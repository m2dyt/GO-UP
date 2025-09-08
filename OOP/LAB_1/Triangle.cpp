#include <iostream>
#include "Triangle.h"



void Triangle::SetABC(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void  Triangle::PrintTriangle() {
    std::cout << "Стороны треугольника" << std::endl;
    std::cout << "сторона a = " << a << std::endl;
    std::cout << "сторона b  = " << b << std::endl;
    std::cout << "сторона c = " << c << std::endl;
}

bool Triangle::IsTriangle() {
    return (a + b > c && a + c > b && b + c > a);
}

bool Triangle::Is90() {
    if (IsTriangle()) {
        return ((a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a));
    }
    else {
        return false;
    }
}

bool Triangle::IsRav2() {
    return (a == b || a == c || b == c);
}

bool Triangle::IsRav3() {
    return (a == b && b == c);
}