#include <iostream>
#include "Rectangle.h"

using namespace std;

int main()
{   
    setlocale(LC_ALL, "rus");
    Rectangle r0;
    Rectangle r1(Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3));
    Rectangle r2(Point(2, 1), Point(6, 1), Point(6, 4), Point(2, 4)); 
    Rectangle r3(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));

    cout << "=== Прямоугольники ===" << endl;
    cout << "r0: "; 
    r0.print();
    cout << "r1: "; 
    r1.print();
    cout << "r2: "; 
    r2.print();
    cout << "r3: "; 
    r3.print();
    cout << endl;

    cout << "Периметры" << endl;
    cout << "r0 " << r0.perimetr()<< endl;
    cout << "r1 " << r1.perimetr() << endl;
    cout << "r2 " << r2.perimetr() << endl;
    cout << "r3 " << r3.perimetr() << endl;
    cout << endl;


    cout << "Сравнение по периметру" << endl;
    if (r1 > r3) cout << "r1 больше r3" << endl;
    if (r3 < r2) cout << "r3 меньше r2" << endl;
    if (r1 == r2) cout << "r1 равен r2 " << endl;
    cout << endl;

    cout << "=== Объединение ===" << endl;
    Rectangle r_union = r1 * r2; 
    cout << "Объединение r1 и r2:" << endl;
    r_union.print();

}

