#pragma once
#include "B.h"

class D2 : virtual private B {
private:
    int d2;
public:
    D2(int b_val, int d2_val); 
    virtual ~D2();
    void show_D2();
};