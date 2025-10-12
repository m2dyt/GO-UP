#pragma once
#include "D2.h"
#include "D3.h"

class D5 : public D2, private D3{
protected:
	int d5;
public:
	D5(int a, int b, int c, int d);
	void show_D5();
	~D5();
};