#include "D2.h"
#include <iostream>
using namespace std;


D2::D2(int b_val, int d2_val) : d2(d2_val) {
    cout << "D2 constr = " << d2_val << "\n" ;
    set_B(b_val); 
    
}

D2::~D2() {
    cout << "D2 destructor\n";
}

void D2::show_D2() {
    cout << "D2= " << d2 << "\n";
    show_B();
}
