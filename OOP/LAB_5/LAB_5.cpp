#include <iostream>
#include "B.h"
#include "D1.h"
#include "D2.h"
#include "D3.h"
#include "D4.h"
#include "D5.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    cout << "ТЕСТИРОВАНИЕ ВСЕХ КЛАССОВ\n";

    
    cout << "1. ТЕСТ КЛАССА B:\n";
    B b(50);
    b.show_B();
    cout << endl;

   
    cout << "2. ТЕСТ КЛАССА D1:\n";
    D1 d1(100, 200);
    d1.show_D1();
    cout << endl;

   
    cout << "3. ТЕСТ КЛАССА D2:\n";
    D2 d2(150, 250);
    d2.show_D2();
    cout << endl;

  
    cout << "4. ТЕСТ КЛАССА D3:\n";
    D3 d3(200, 300);
    d3.show_D3();
    cout << endl;

 
    cout << "5. ТЕСТ КЛАССА D4:\n";
    D4 d4(10, 20, 30);
    d4.show_D4();
    cout << endl;

 
    cout << "6. ТЕСТ КЛАССА D5:\n";
    D5 d5(5, 15, 25, 35);
    d5.show_D5();
    cout << endl;

    return 0;
}