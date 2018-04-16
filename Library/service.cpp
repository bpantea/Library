#include "service.h"

Service::Service()
{
}

void Service::add(const string& title, const string& author, const string& genre, const int& year)
{
	Book b{ title, author, genre, year };
	validator.validateBook(b);
	repo.add(b);
}

void Service::modify(const string& oldTitle, const string& oldAuthor, const string& title, const string& author, const string& genre, const int& year)
{
	Book oldBook{ oldTitle, oldAuthor, "", 0 };
	Book newBook{ title, author, genre, year };
	validator.validateBook(newBook);
	repo.modify(oldBook, newBook);
}

void Service::remove(const string& title, const string& author)
{
	Book b{ title, author, "", 0 };
	repo.remove(b);
}

SimplyLinkedList<Book>& Service::getAll()
{
	return repo.getAllElements();
}

vector<Book> Service::filter(bool(*cmpFunction)(const Book& b1, const Book& b2), const Book& b2) noexcept
{
	vector<Book> v;
	v.clear();
	for (const auto& b : repo.getAllElements())
		if (cmpFunction(b, b2))
			v.push_back(b);
	return v;
}

vector<Book> Service::sortBooks(bool(*lessFunction)(const Book& b1, const Book& b2)) noexcept
{
	vector<Book> v;
	for (const auto& it : repo.getAllElements())
		v.push_back(it);
	sort(v.begin(), v.end(), lessFunction);
	return v;
}