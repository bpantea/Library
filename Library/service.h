#pragma once

#include "repository.h"
#include "book.h"
#include <algorithm>
#include "validator.h"
#include <random>
#include "undo.h"
#include <stack>
#include <memory>

using std::unique_ptr;

class Service
{
private:
	stack<unique_ptr<Undo<Book>>> undoStack;
	AbstractRepository<Book>& repo;
	Repository<Book> cart{};
	Validator validator{};

public:
	/*
	The constructor of Service class.
	*/
	Service(AbstractRepository<Book>& repo) noexcept : repo{ repo } {}

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
	vector<Book> getAll() noexcept {
		return repo.getAllElements();
	}

	/*
	Filter by type
	*/
	vector<Book> filter(bool(*cmpFunction)(const Book& b1, const Book& b2), const Book&) noexcept;

	/*
	Sort books
	*/
	vector<Book> sortBooks(bool(*lessFunction)(const Book& b1, const Book& b2)) noexcept;

	/*
	Add book to cart by title.
	*/
	void addToCart(const string& title) {
		Book b = repo.getElement(repo.getPosition(Book{ title, "", "", 0 }));
		cart.add(b);
	}

	/*
	Clear cart
	*/
	void clearCart() {
		cart.clearRepository();
	}

	/*
	Generates randomly a cart of size = size.
	*/
	void generateCart(const int& size) {
		clearCart();
		if (size > repo.getSize())
			throw(RepositoryException("Cart size is bigger than list size"));
		
		vector<Book> v{ repo.getAllElements() };
		random_device rd;
		mt19937 g(rd());
		shuffle(v.begin(), v.end(), g);
		for (int i = 0; i < size; i++)
			cart.add(v[i]);
	}

	/*
	Gets cart vector.
	*/
	vector<Book> getCart() noexcept {
		return cart.getAllElements();
	}

	/*
	Returnes cart size.
	*/
	int getCartSize() const noexcept {
		return cart.getSize();
	}

	/*
	Undo function.
	*/
	void undo()
	{
		if (undoStack.size() == 0)
			throw Exception("Can't undo.");
		undoStack.top()->doUndo();
		undoStack.pop();
	}

	/*
	Export cart to html file.
	*/
	void exportCartToHtml(const string& fileName) {
		ofstream g(fileName);
		if (!g.is_open())
			throw Exception("File cannot be opened.");
		g << "<html><body>\n";
		g << "<table border=\"1\" style=\"width:100%\">" << '\n';
		for (const auto& it : getCart())
		{
			g << "<tr> \n";
			g << "<td>" << it.getTitle() << "</td> \n";
			g << "<td>" << it.getAuthor() << "</td> \n";
			g << "<td>" << it.getGenre() << "</td> \n";
			g << "<td>" << it.getYear() << "</td> \n";
			g << "</tr> \n";
		}
		g << "</table> \n";
		g << "</body></html> \n";
		g.close();
	}

	/*
	Export cart to cvs file.
	*/
	void exportCartToCSV(const string& fileName) {
		ofstream g(fileName);
		if (!g.is_open())
			throw Exception("File cannot be opened.");
		for (const auto& it : getCart())
			g << it << '\n';
		g.close();
	}
};