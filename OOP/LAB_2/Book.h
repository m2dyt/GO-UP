#pragma once
#include <string>


class Book {
private:
	std::string title;
	std::string author;
	int year;
public:
	Book();
	Book(const std::string& title, const std::string& author, int year, char chek='*');
	Book(Book& other_book);
	~Book();

	void SetTitle(const std::string& t);
	void SetAuthor(const std::string& a);
	void SetYear(int y);

	std::string GetTitle();
	std::string GetAuthor();
	int GetYear();

	void PrintBook();
};