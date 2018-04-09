#pragma once
#include "book.h"
#include "exceptions.h"
#include <vector>
#include <string>

using namespace std;

class Validator
{
public:
	void validateBook(const Book& b) const;
};