#include "D4.h"
#include <iostream>
using namespace std;

D4::D4(int b_val, int d1_val, int d4_val) : D1(b_val, d1_val), d4(d4_val) {}

D4::~D4() {
    cout << "D4 destructor\n";
}

void D4::show_D4() {
    cout << "D4= " << d4 << "\n";
    show_D1();
}