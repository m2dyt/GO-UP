#include <iostream>
#include "Book.h"

Book::Book() : title("����������"), author("����������"), year(0) {}

Book::Book(const std::string& t, const std::string& a, int y, char c)
	: title(t), author(a), year(y) {
	if (c != '*') {
		if (!a.empty() && a[0] != c) {
			std::cout << "������ ������ ����� ������ " << a << " ��� " << a[0] << " ,� �� " << c << std::endl;
		}
		else {
			std::cout << "����� ���������� " << std::endl;
		}
	}
}

Book::Book(Book& other_book)
	: title(other_book.title), author(other_book.author), year(other_book.year) {}

Book::~Book() {
	std::cout << "��������� �����: " << title << std::endl;
}

void Book::SetAuthor(const std::string& a) {
	author = a;
}

void Book::SetTitle(const std::string& t) {
	title = t;
}

void Book::SetYear(int y) {
	year = y;
}

std::string Book::GetAuthor() {
	return author;
}

std::string Book::GetTitle() {
	return title;
}

int Book::GetYear() {
	return year;
}

void Book::PrintBook() {
	std::cout << "�����: " << title << "\n" << "�����: "
	<< author << "\n" << "���: " << year << std::endl;
}
