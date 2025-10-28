#include "Array.hpp"

int main() {
	setlocale(LC_ALL, "Russian");


	try {
		std::cout << "1) Проверка создания массива корректного размера:\n";
		double nums[12] = { 1.5, -2.3, 0, 4.2, -1.1, 3.3, 0, 0, 2.2, -0.5, 6.6, 1.1 };
		Array arr(nums, 12);
		std::cout << "Массив успешно создан:\n";
		arr.print();

		std::cout << "\nМаксимальный элемент массива: " << arr.FindMaxElement() << "\n";
		std::cout << "Сумма элементов до последнего положительного элемента: "
			<< arr.SumBeforeLastPositive() << "\n";

		std::cout << "\n2) Сжатие массива \n";
		arr.Compress(1.0, 3.0);
		arr.print();

		std::cout << "\n3) Проверка выхода за границы массива:\n";
		try {
			arr[20] = 5;
		}
		catch (const MyException& e) {
			std::cout << "Исключение перехвачено: " << e.what() << "\n";
		}

		std::cout << "\n4) Проверка массива без положительных элементов:\n";
		double negativeOnly[12] = { -5, -3, -2, -7, -9, -1, -8, -4, -6, -2, -3, -10 };
		Array arr2(negativeOnly, 12);
		arr2.print();
		try {
			arr2.SumBeforeLastPositive();
		}
		catch (const MyException& e) {
			std::cout << "Исключение перехвачено: " << e.what() << "\n";
		}

		std::cout << "\n5) Проверка слишком большого массива:\n";
		double bigArray[20] = { 0 };
		try {
			Array tooBig(bigArray, 20);
		}
		catch (const MyException& e) {
			std::cout << "Исключение перехвачено: " << e.what() << "\n";
		}

		std::cout << "\n6) Проверка массива нулевой длины:\n";
		try {
			Array zeroArray(nullptr, 0);
		}
		catch (const std::exception& e) {
			std::cout << "Исключение перехвачено: " << e.what() << "\n";
		}

	}
	catch (const std::exception& e) {
		std::cout << "\nОбнаружено непредвиденное исключение: " << e.what() << "\n";
	}

	return 0;
}
