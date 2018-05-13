#pragma once

#include "service.h"
#include <iostream>

class UI
{
private:
	Service& service;

	/*
	Print user options.
	*/
	void printMenu() const;

	/*
	Add an element.
	*/
	void addUI();

	/*
	Print all elements
	*/
	void printAllElemsUI();

	/*
	Print a book.
	*/
	void printBook(const Book& b) const;

	/*
	Modify a book.
	*/
	void modifyBook();

	/*
	Delete a book.
	*/
	void removeBook();

	/*
	Filter books by title.
	*/
	void filterTitle();

	/*
	Filter books by year
	*/
	void filterYear();

	/*
	Sort books by title
	*/
	void sortTitle();

	/*
	Sort books by author
	*/
	void sortAuthor();

	/*
	Sort books by genre.
	*/
	void sortGenre();

	/*
	Add book to cart by title.
	*/
	void addToCart();

	/*
	Clear cart.
	*/
	void clearCart();

	/*
	Add cart random.
	*/
	void randomFillCart();

	/*
	Print all books in cart.
	*/
	void printCart();
public:
	/*
	Constructor of UI class.
	*/
	UI(Service& service) noexcept : service{ service } {}

	/*
	Add some books.
	*/
	void initializeBooks();

	/*
	Undo function.
	*/
	void undo() {
		service.undo();
	}

	/*
	Export cart to html file.
	*/
	void exportHtml();

	/*
	Export cart to cvs file.
	*/
	void exportCvs();

	/*
	Run the UI Console.
	*/
	void run();
};