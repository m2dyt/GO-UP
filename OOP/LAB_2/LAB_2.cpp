#include <iostream>
#include "Book.h"

int main()
{   
    setlocale(LC_ALL, "rus");
    Book book_1;
    book_1.PrintBook();
    std::cout << "---------------------------------" << std::endl;

    Book book_2("Преступление и наказание", "Достоевский", 1866);
    book_2.PrintBook();
    std::cout << "---------------------------------" << std::endl;

    Book book_3("Евгений Онегин", "Пушкин", 1833, 'П');
    book_3.PrintBook();
    std::cout << "---------------------------------" << std::endl;

    Book book_4("Мёртвые души", "Гоголь", 1842, 'А');
    book_4. PrintBook();
    std::cout << "---------------------------" << std::endl;

    Book book_5 = book_2;
    book_5.PrintBook();
    std::cout << "---------------------------" << std::endl;

    return 0;
}

