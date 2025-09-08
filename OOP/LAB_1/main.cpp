#include <iostream>
#include "Triangle.h"



int main() {
    setlocale(LC_ALL, "Russian");
    Triangle triangle1;
    int a, b, c;
    std::cout << "Введите сторону а ";
    std::cin >> a;
    std::cout << "Введите сторону b ";
    std::cin >> b;
    std::cout << "Введите сторону c ";
    std::cin >> c;
    triangle1.SetABC(a, b, c);
    triangle1.PrintTriangle();
    if (triangle1.IsTriangle()) {
        std::cout << "Треугольник существует "<< std::endl;

        if (triangle1.Is90()) {
            std::cout << "Труегольник прямоугольный" << std::endl;
        }
        else {
            std::cout << "Труегольник не прямоугольный" << std::endl;
        }

        if (triangle1.IsRav3()) {
            std::cout << "Треуголник равносторонний " << std::endl;
            std::cout << "Не равнобедренный так как равносторонний " << std::endl;
        }
        else {
            std::cout << "Треуголник не равносторонний " << std::endl;
            if (triangle1.IsRav2()) {
                std::cout << "Треугольник равнобедренный " << std::endl;
            }
            else {
                std::cout << "Треугольник не равнобедренный " << std::endl;
            }
        }

       

    }
    else {
        std::cout << "Труегольник не существует " << std::endl;
    }

    return 0;
}
