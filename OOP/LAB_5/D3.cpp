#include "D3.h"
#include <iostream>
using namespace std;


D3::D3(int b_val, int d3_val) : d3(d3_val) {
    cout << "D3 constr = " << d3_val << "\n";
    set_B(b_val); 
}

D3::~D3() {
    cout << "D3 destructor\n";
}

void D3::show_D3() {
    cout << "D3= " << d3 << "\n";
    show_B();
}
