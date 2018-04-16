#include "tests.h"

void Tests::testBook()
{
	Book b{ "title", "author", "genre", 2000 };
	assert(b.getAuthor() == "author");
	assert(b.getGenre() == "genre");
	b.setTitle("title2");
	assert(b.getTitle() == "title2");
	assert(b.getYear() == 2000);
	b.setYear(100);
	b.setAuthor("Ion");
	Book b2{};
	b2.setTitle("title2");
	b2.setAuthor("Ion");
	assert(b == b2);
}

void Tests::testRepository()
{
	Repository<int> repo{};
	
	repo.add(1);
	try
	{
		repo.add(1);
		assert(false);
	}
	catch (RepositoryException) {}
	repo.modify(1, 2);
	repo.add(1);
	repo.remove(1);
	assert(repo.getAllElements().size() == 1);
	try
	{
		repo.remove(1);
		assert(false);
	}
	catch (RepositoryException) {}
	try
	{
		repo.modify(1, 2);
		assert(false);
	}
	catch (RepositoryException& ex) {
		assert(ex.getMessage().size() != 0);
	}
}

void testValidator()
{
	Validator validator;
	Book b{ "", "a", "b", 100 };
	try
	{
		validator.validateBook(b);
	}
	catch (ValidateException)
	{ }
	b.setGenre("");
	b.setTitle("");
	b.setAuthor("");
	b.setYear(-1);
	try
	{
		validator.validateBook(b);
	}
	catch (ValidateException& ex)
	{ 
		assert(ex.getMessage().size() != 0);
	}
}

void Tests::testServiceAdd()
{
	Service serv{};
	serv.add("a", "b", "c", 2000);
	try
	{
		serv.add("a", "b", "c", 2000);
	}
	catch (RepositoryException) {}

}

void Tests::testServiceModify()
{
	Service serv{};
	serv.add("a", "a", "genre", 100);
	serv.modify("a", "a", "aa", "aa", "genre", 200);
	try {
		serv.modify("a", "a", "aa", "aa", "genre", 200);
	}
	catch (RepositoryException) {}
}

void Tests::testServiceRemove()
{
	Service serv{};
	try {
		serv.remove("a", "a");
	}
	catch (RepositoryException) {}
	serv.add("a", "a", "c", 0);
	serv.remove("a", "a");
	assert(serv.getAll().size() == 0);
}

void Tests::testServiceSort()
{
	Service serv{};
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("b", "c", "a", 1);
	assert(serv.sortBooks(Book::lessOperatorTitle)[0].getTitle() == "a");
	assert(serv.sortBooks(Book::lessOperatorAuthor)[1].getTitle() == "c");
	assert(serv.sortBooks(Book::lessOperatorGenre)[0].getYear() == 1);
}

void Tests::testServiceFilter()
{
	Service serv{};
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("a", "c", "a", 1);
	assert(serv.filter(Book::compareTitle, Book{ "a", "", "", 0 }).size() == 2);
	vector<Book> v = serv.filter(Book::compareYear, Book{ "", "", "", 3 });
	assert(v.size() == 2);
}

void Tests::testLinkedList()
{
	SimplyLinkedList<int> v{};
	assert(v.size() == 0);
	v.push_back(1);
	assert(v.size() == 1);
	assert(v[0] == 1);
	v.push_back(2);
	assert(v[1] == 2);
	assert(v.size() == 2);
	v.push_back(3);
	v[0] = 4;
	assert(v[0] == 4);
	assert(v[2] == 3);
	
	
	v.erase(0);
	//v.erase(1);
	assert(v.size() == 2);
	v.erase(1);
	
	v[0] = 2;
	assert(v.size() == 1);
	assert(v[0] == 2);
	
	v.push_back(5);
	v[1] = 10;
	assert(v[1] == 10);
	v[0] = 0;
	assert(v[0] == 0);

	v.erase(1);
	v.erase(0);

	try
	{
		v.erase(100);
		assert(false);
	}
	catch (LinkedListException) {}
	try
	{
		v[100] = 1;
		assert(false);
	}
	catch (LinkedListException) {}
}

void Tests::run()
{
	testBook();
	testRepository();
	testServiceAdd();
	testServiceModify();
	testServiceRemove();
	testServiceSort();
	testServiceFilter();
	testValidator();

	testLinkedList();
}