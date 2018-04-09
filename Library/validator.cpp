#include "validator.h"

void Validator::validateBook(const Book & b) const
{
	vector<string> v;
	v.clear();
	if (b.getTitle().size() == 0)
		v.push_back("Title must be filled.");
	if (b.getAuthor().size() == 0)
		v.push_back("Author must be filled.");
	if (b.getGenre().size() == 0)
		v.push_back("Genre must be filled.");
	if (b.getYear() < 0 || b.getYear() > 2020)
		v.push_back("Incorrect year.");

	if (v.size() != 0)
		throw ValidateException(v);
}
