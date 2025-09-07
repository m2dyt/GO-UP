#include <iostream>
#include <cstdlib>


void PrintMas(int* A, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << "\n";
}


int SumPosNumber(int* A, int n) {
    int sum_n = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] > 0) {
            sum_n += A[i];
        }
    }
    return sum_n;
}


int CountNegNumber(int count_n) {
    return count_n;
}


int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    int count_n = 0;
    std::cout << "Введите кол-во элементов в массиве ";
    std::cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n - ((n / 2) - 1);
        if (A[i] < 0) {
            count_n++;
        }
    }

    std::cout << "Сгенерированный массив " << std::endl;
    PrintMas(A, n);

    int exit = 1;
    while (exit) {
        std::cout << "Выберете действие\n";
        std::cout << "1 - Подсчитать сумму положительных элементов\n";
        std::cout << "2 - Подсчитать количество отрицательных элементов\n";
        std::cout << "0 - Выход\n";
        int user_choose;
        std::cin >> user_choose;
        switch (user_choose) {
        case 0:
            exit = 0;
            break;
        case 1:
            std::cout << "Сумма положительных элементов " << SumPosNumber(A, n) << std::endl;
            break;
        case 2:
            std::cout << "Кол-во отрицательных элементов " << CountNegNumber(count_n) << std::endl;
            break;
        default:
            std::cout << "Неверный выбор\n";
            break;
        }
    }

    return 0;
}
