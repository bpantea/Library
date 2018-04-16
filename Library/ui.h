#pragma once

#include "service.h"
#include <iostream>

class UI
{
private:
	Service service;

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
public:
	/*
	Constructor of UI class.
	*/
	UI() {
		service = Service();
	}

	/*
	Add some books.
	*/
	void initializeBooks();

	/*
	Run the UI Console.
	*/
	void run();
};