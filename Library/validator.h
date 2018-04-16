#pragma once
#include "book.h"
#include "exceptions.h"
#include <vector>
#include <string>

using namespace std;

class Validator
{
public:
	/*
	Validates a book.
	b - Book to be validated.
	It raises an ValidatorException if the book hasn't passed validation.
	*/
	void validateBook(const Book& b) const;
};