#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <cstring>

class MyException : public std::exception {
private:
	std::string m_Messege;
public:
	explicit MyException(const char* message);
	~MyException() override = default;
	const char* what() const noexcept override;
};


class Array {
private:
	double m_array[12] = {};
public:
	Array(const double* array, const int size);
	~Array();

	double& operator[](int index);
	void print();

	double FindMaxElement();
	double SumBeforeLastPositive();
	void Compress(double a, double b);
};