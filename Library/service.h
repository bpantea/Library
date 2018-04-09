#pragma once

#include "repository.h"
#include "book.h"
#include <algorithm>
#include "validator.h"

class Service
{
private:
	Repository<Book> repo = Repository<Book>();
	Validator validator{};
public:
	/*
	The constructor of Service class.
	*/
	Service();

	/*
	Adds a book to the repo.
	@title, author, genre, year Info of the book.
	@return 1 if the book was added 0 otherwise.
	*/
	void add(const string& title, const string& author, const string& genre, const int& year);

	/*
	Modifies a book from the repository.
	First book is given by title and author
	title, author, genre and year are given after.
	@return 1 if the book was updated or 0 otherwise.
	*/
	void modify(const string& oldTitle, const string& oldAuthor, const string& title, const string& author, const string& genre, const int& year);

	/*
	Deletes a book from the repository.
	@param title Title of the book
	@param author Author of the book
	@return 1 if the book was deleted 0 otherwise.
	*/
	void remove(const string& title, const string& author);

	/*
	Get all books.
	*/
	const vector<Book>& getAll() const;

	/*
	Filter by type
	*/
	vector<Book> filter(bool(*cmpFunction)(const Book& b1, const Book& b2), const Book& b2) const noexcept;

	/*
	Sort books
	*/
	vector<Book> sortBooks(bool(*lessFunction)(const Book& b1, const Book& b2)) const noexcept;
};