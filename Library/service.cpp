#include "service.h"


void Service::add(const string& title, const string& author, const string& genre, const int& year)
{
	Book b{ title, author, genre, year };
	validator.validateBook(b);
	repo.add(b);

	undoStack.push(std::make_unique<AddUndo<Book>>(repo, b));
}

void Service::modify(const string& oldTitle, const string& oldAuthor, const string& title, const string& author, const string& genre, const int& year)
{
	Book oldBook{ oldTitle, oldAuthor, "", 0 };
	oldBook = repo.getElement(repo.getPosition(oldBook));
	Book newBook{ title, author, genre, year };
	validator.validateBook(newBook);
	repo.modify(oldBook, newBook);

	undoStack.push(std::make_unique<ModifyUndo<Book>>(repo, oldBook, newBook));
}

void Service::remove(const string& title, const string& author)
{
	Book b{ title, author, "", 0 };
	b = repo.getElement(repo.getPosition(b));
	repo.remove(b);

	undoStack.push(std::make_unique<RemoveUndo<Book>>(repo, b));
}

vector<Book> Service::filter(bool(*cmpFunction)(const Book& b1, const Book& b2), const Book& b3) noexcept
{
	vector<Book> v;
	v.clear();
	for (const auto& b : repo.getAllElements())
		if (cmpFunction(b, b3))
			v.push_back(b);
	//copy_if(repo.getAllElements().begin(), repo.getAllElements().end(), v, cmpFunction);
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