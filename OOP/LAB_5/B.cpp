#include "B.h"
#include <iostream>
using namespace std;

B::B() : b(0) {
    cout << "B constr = " << 0 << "\n";
}

B::~B() {
    cout << "B destructor\n";
}

void B::show_B() {
    cout << "B= " << b << "\n";
}

void B::set_B(int b_val) {
    b = b_val;
    cout << "B setter = " << b_val << "\n";
}