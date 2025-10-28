#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <numeric>  
#include <cmath>    

template<typename T>
class Vector
{
public:
    Vector(const size_t size, const T m1, const T m2)
    {
        m_Vector = std::vector<T>(size);
        static std::random_device rd;
        std::mt19937_64 generator(rd());
        std::uniform_real_distribution<double> distribution(m1, m2);
        for (size_t i = 0; i < size; i++)
            m_Vector[i] = static_cast<T>(distribution(generator));
    }

    ~Vector() = default;

    // Индексация []
    T& operator [] (const size_t index)
    {
        return m_Vector[index];
    }

    // Вывод вектора
    void Print(const char* message = "") const
    {
        if (message && message[0] != '\0')
            std::cout << message;
        for (size_t i = 0; i < m_Vector.size(); i++)
        {
            std::cout << std::setw(6) << m_Vector[i];
            if (i != m_Vector.size() - 1) std::cout << " ";
        }
        std::cout << "\n";
    }

    // Вычисление среднего значения
    double Average() const
    {
        double sum = std::accumulate(m_Vector.begin(), m_Vector.end(), 0.0);
        return sum / static_cast<double>(m_Vector.size());
    }

    // Поэлементное сложение с другим вектором
    Vector<T> Add(const Vector<T>& other) const
    {
        Vector<T> result = *this;
        std::transform(m_Vector.begin(), m_Vector.end(),
            other.m_Vector.begin(),
            result.m_Vector.begin(),
            std::plus<T>());
        return result;
    }

    // Подсчёт элементов с |x| == 5
    size_t CountAbsEqual5() const
    {
        return std::count_if(m_Vector.begin(), m_Vector.end(),
            [](const T& x) { return std::abs(x) == 5; });
    }

    // Возврат размера
    size_t Size() const { return m_Vector.size(); }

private:
    std::vector<T> m_Vector;
};
