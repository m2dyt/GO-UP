#include "D3.h"
#include <iostream>
using namespace std;

D3::D3(int b_val, int d3_val) : B(b_val), d3(d3_val) {}

D3::~D3() {
    cout << "D3 destructor\n";
}

void D3::show_D3() {
    cout << "D3= " << d3 << "\n";
    show_B();
}