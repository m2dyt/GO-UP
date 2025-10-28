#include "Array.hpp"

MyException::MyException(const char* message)
	: m_Message(message) {
}

const char* MyException::what() const noexcept {
	return m_Message.c_str();
}

Array::Array(const double* array, const int size) {
	if (size > 12) {
		throw MyException("Ошибка: входной массив слишком большой!");
	}
	if (size <= 0) {
		throw std::invalid_argument("Ошибка: размер массива должен быть положительным!");
	}
	std::memcpy(m_array, array, size * sizeof(double));
}

Array::~Array() = default;

double& Array::operator[](int index) {
	if (index < 0 || index >= 12) {
		throw MyException("Ошибка: выход за границы массива!");
	}
	return m_array[index];
}

void Array::print() {
	for (int i = 0; i < 12; ++i) {
		std::cout << m_array[i] << " ";
	}
	std::cout << "\n";
}

double Array::FindMaxElement() {
	double max_val = m_array[0];
	for (int i = 1; i < 12; i++) {
		if (m_array[i] > max_val) {
			max_val = m_array[i];
		}
	}
	return max_val;
}

double Array::SumBeforeLastPositive() {
	int last_pos = -1;
	for (int i = 0; i < 12; ++i) {
		if (m_array[i] > 0) last_pos = i;
	}
	if (last_pos == -1) {
		throw MyException("Ошибка: в массиве нет положительных элементов!");
	}
	double sum = 0;
	for (int i = 0; i < last_pos; ++i) {
		sum += m_array[i];
	}
	return sum;
}


void Array::Compress(double a, double b) {

	double temp[12] = {};
	int index = 0;

	for (int i = 0; i < 12; ++i) {
		if (std::abs(m_array[i]) < a || std::abs(m_array[i]) > b) {
			temp[index++] = m_array[i];
		}
	}

	while (index < 12) temp[index++] = 0;

	std::memcpy(m_array, temp, 12 * sizeof(double));
}
