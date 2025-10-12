#include "B.h"
#include <iostream>
using namespace std;

B::B(int b_val) : b(b_val) {}

B::~B() {
    cout << "B destructor\n";
}

void B::show_B() {
    cout << "B= " << b << "\n";
}
