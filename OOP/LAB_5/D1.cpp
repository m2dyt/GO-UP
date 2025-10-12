#include "D1.h"
#include <iostream>
using namespace std;

D1::D1(int b_val, int d1_val) : B(b_val), d1(d1_val) {}

D1::~D1() {
    cout << "D1 destructor\n";
}

void D1::show_D1() {
    cout << "D1= " << d1 << "\n";
    show_B();
}