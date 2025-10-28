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

    cout << "класс D4\n";
    D4 d4(10, 20, 30);

    d4.show_D4();
    cout << endl;

    cout << "класс D5 \n";
    D5 d5(5, 15, 25, 35);
    d5.show_D5();
    cout << endl;

    return 0;
}