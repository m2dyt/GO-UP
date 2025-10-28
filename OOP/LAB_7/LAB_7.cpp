#include <cstdint>
#include <iostream>
#include "Vector.hpp"

template<typename T>
void Demonstrate(const char* name)
{
    std::cout << "=== Демонстрация для типа: " << name << " ===\n";

    // 1. Создаём первый вектор [-50, 50]
    Vector<T> v1(10, -50, 50);
    v1.Print("Первый вектор (0..10): ");

    // 2. Вычисляем среднее значение
    double avg = v1.Average();
    std::cout << "Среднее значение элементов первого вектора: " << avg << "\n\n";

    // 3. Создаём второй вектор [-10, 10]
    Vector<T> v2(10, -50, 50);
    v2.Print("Второй вектор (-10..10): ");

    // 4. Складываем поэлементно
    Vector<T> v3 = v1.Add(v2);
    v3.Print("Результирующий вектор (v1 + v2): ");

    // 5. Считаем количество элементов, где |x| == 5
    size_t count = v3.CountAbsEqual5();
    std::cout << "Количество элементов с |x| = 5: " << count << "\n\n";
}

int32_t main(int32_t argc, char** argv)
{
    setlocale(LC_ALL, "rus");
    Demonstrate<int>("int");
    Demonstrate<float>("float");
    Demonstrate<double>("double");
    std::cin.get();
}
