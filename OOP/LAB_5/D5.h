#pragma once
#include "D2.h"
#include "D3.h"

class D5 : public D2, private D3 {
private:
    int d5;
public:
    D5(int b_val, int d2_val, int d3_val, int d5_val); 
    void show_D5();
    ~D5();
};