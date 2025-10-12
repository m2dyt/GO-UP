#include "D5.h"
#include <iostream>
using namespace std;
#include "D5.h"
#include <iostream>
using namespace std;

D5::D5(int b_val, int d2_val, int d3_val, int d5_val)
    : D2(b_val, d2_val), D3(b_val, d3_val), d5(d5_val) {
}

D5::~D5() {
    cout << "D5 destructor\n";
}

void D5::show_D5() {
    cout << "D5= " << d5 << "\n";
    show_D2();
    show_D3();
}