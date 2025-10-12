#pragma once
#include "B.h"

class D3 : virtual private B {
private:
    int d3;
public:
    D3(int b_val, int d3_val);
    virtual ~D3();
    void show_D3();
};