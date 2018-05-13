#pragma once

#include <string>
#include <iostream>

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
	Book() noexcept {
		this->author = "";
		this->genre = "";
		this->title = "";
		this->year = 0;
	}

	/*
	Represents the constructor of the class Book.
		
	@param title The title of the book
	@param author The author of the book
	@param genre The genre of the book
	@param year The publishing year of the book
	*/
	Book(const string& title, const string& author, const string& genre, const int& year) : author{ author }, title{ title }, genre{ genre }, year{ year } {}

	/*
	@return the title of the book.
	*/
	string getTitle() const noexcept {
		return title;
	}

	/*
	@return the author of the book.
	*/
	string getAuthor() const noexcept {
		return author;
	}

	/*
	@return the genre of the book.
	*/
	string getGenre() const noexcept {
		return genre;
	}
	/*
	@return the publishing year of the book.
	*/
	int getYear() const noexcept {
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
	void setYear(const int& newYear) noexcept {
		this->year = newYear;
	}

	/*
	Overrides the == operator.
	@param other Another book to compare.
	*/
	bool operator==(const Book& other) const noexcept {
		return title == other.title;
	}

	/*
	Compare function by title.
	@param b Book to be compared
	@param s String to be compared
	@return true if the tile of b is equal to s; false otherwise
	*/
	static bool compareTitle(const Book& b1, const Book& b2) noexcept {
		return b1.getTitle() == b2.getTitle();
	}

	/*
	Compare by publishing year.
	@param b Book to be compared
	@param year Publishing year to be compared.
	@return true if year of book is greater than year; false otherwise
	*/
	static bool compareYear(const Book& b1, const Book& b2) noexcept {
		return b1.getYear() >= b2.getYear();
	}

	/*
	Less than operator. It compares books by title.
	*/
	static bool lessOperatorTitle(const Book& b1, const Book& b2) noexcept {
		return b1.getTitle() < b2.getTitle();
	}

	/*
	Less than operator. It compares books by author.
	*/
	static bool lessOperatorAuthor(const Book& b1, const Book& b2) noexcept {
		return b1.getAuthor() < b2.getAuthor();
	}

	/*
	Less than operator. It compares books by genre and year.
	*/
	static bool lessOperatorGenre(const Book& b1, const Book& b2) noexcept {
		if (b1.getGenre() == b2.getGenre())
			return b1.getYear() < b2.getYear();
		return b1.getGenre() < b2.getGenre();
	}

	/*
	Override stream operator<<.
	*/
	friend ostream& operator<<(ostream& out, const Book& b) {
		out << b.author << ',';
		out << b.genre << ',';
		out << b.title << ',';
		out << b.year << ',';
		return out;
	}

	/*
	Override stream operator>>.
	*/
	friend istream& operator>>(istream& in, Book& b) {
		string s[4];
		for (int i = 0; i < 4; i++)
			getline(in, s[i], ',');
		if (s[3] == "")
			return in;
		b.setAuthor(s[0]);
		b.setGenre(s[1]);
		b.setTitle(s[2]);
		b.setYear(stoi(s[3]));

		getline(in, s[0]);
		
		return in;
	}
};