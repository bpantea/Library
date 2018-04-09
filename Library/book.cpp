#include "book.h"

Book::Book()
{
	this->author = "";
	this->genre = "";
	this->title = "";
	this->year = 0;
}

Book::Book(const string& title, const string& author, const string& genre, const int& year) : title{title}, 
author{author}, genre{genre}, year{year}
{
	
}