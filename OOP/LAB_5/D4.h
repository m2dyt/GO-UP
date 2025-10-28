#pragma once
#include "D1.h"

class D4 : private D1 {
private:
    int d4;
public:
    D4(int b_val, int d1_val, int d4_val); // Конструктор с параметрами
    ~D4();
    void show_D4();

};