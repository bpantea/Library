#pragma once

#include <string>

using namespace std;

class Book {
private:
	string title, author, genre;
	int year;

public:
	/*
	Represents the default constructor of the class Book.
	title, author, genre will be initialized as empty strings. Year as 0
	*/
	Book();

	/*
	Represents the constructor of the class Book.
		
	@param title The title of the book
	@param author The author of the book
	@param genre The genre of the book
	@param year The publishing year of the book
	*/
	Book(const string& title, const string& author, const string& genre, const int& year);

	/*
	@return the title of the book.
	*/
	string getTitle() const {
		return title;
	}

	/*
	@return the author of the book.
	*/
	string getAuthor() const {
		return author;
	}

	/*
	@return the genre of the book.
	*/
	string getGenre() const {
		return genre;
	}
	/*
	@return the publishing year of the book.
	*/
	int getYear() const {
		return year;
	}

	/*
	Sets the title of the book.

	@param title Title of the book.
	*/
	void setTitle(const string& newTitle) {
		this->title = newTitle;
	}

	/*
	Sets the author of the book.
		
	@param author The author of the book.
	*/
	void setAuthor(const string& newAuthor) {
		this->author = newAuthor;
	}

	/*
	Sets the genre of the book.

	@param genre The genre of the book.
	*/
	void setGenre(const string& newGenre) {
		this->genre = newGenre;
	}

	/*
	Sets the publishing year of the book.

	@param year The publishing year of the book.
	*/
	void setYear(const int& newYear) {
		this->year = newYear;
	}

	/*
	Overrides the == operator.
	@param other Another book to compare.
	*/
	bool operator==(const Book& other) const {
		return author == other.author && title == other.title;
	}

	/*
	Compare function by title.
	@param b Book to be compared
	@param s String to be compared
	@return true if the tile of b is equal to s; false otherwise
	*/
	static bool compareTitle(const Book& b1, const Book& b2) {
		return b1.getTitle() == b2.getTitle();
	}

	/*
	Compare by publishing year.
	@param b Book to be compared
	@param year Publishing year to be compared.
	@return true if year of book is greater than year; false otherwise
	*/
	static bool compareYear(const Book& b1, const Book& b2) {
		return b1.getYear() >= b2.getYear();
	}

	/*
	Less than operator. It compares books by title.
	*/
	static bool lessOperatorTitle(const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle();
	}

	/*
	Less than operator. It compares books by author.
	*/
	static bool lessOperatorAuthor(const Book& b1, const Book& b2) {
		return b1.getAuthor() < b2.getAuthor();
	}

	/*
	Less than operator. It compares books by genre and year.
	*/
	static bool lessOperatorGenre(const Book& b1, const Book& b2) {
		if (b1.getGenre() == b2.getGenre())
			return b1.getYear() < b2.getYear();
		return b1.getGenre() < b2.getGenre();
	}
};