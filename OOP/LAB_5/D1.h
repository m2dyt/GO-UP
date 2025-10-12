#pragma once
#include "B.h"

class D1 : public B {
private:
    int d1;
public:
    D1(int b_val, int d1_val);
    virtual ~D1();
    void show_D1();
};  