#include <iostream>
#include "Angle.h"
#include "Triangle.h"

int main()
{   
    setlocale(LC_ALL, "rus");
    Angle angle_1(500);
    angle_1.print_A();
    std::cout << "\n";

    Angle angle_2(80);
    angle_2.print_A();
    std::cout << "\n";

    Angle angle_3 = angle_1 + angle_2;
    angle_3.print_A();
    std::cout << "\n";

    Angle angle_4 = angle_1 - angle_2;
    angle_4.print_A();
    std::cout << "\n";

    Angle angle_5(90);
    Triangle tri1(3, 4, 5, angle_5);
    tri1.print_T();
    std::cout << "\n";

    Angle angle_6(60);
    Triangle tri2(3, 4, 5, angle_6);
    tri2.print_T();
    std::cout << "\n";

    Angle angle_7(50);
    Triangle tri3(1, 2, 10, angle_7);
    tri3.print_T();
    std::cout << "\n";

    Angle angle_8(90);
    Triangle tri4(6, 8, 1000, angle_8);
    tri4.print_T();
}
