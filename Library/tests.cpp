#include "tests.h"
#include <sstream>
#include <iostream>

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


	/*Test stream operators*/
	stringstream out;
	b = Book{ "a", "a", "a", 1 };
	out << b;
	assert(out.str() == "a,a,a,1,");
	istringstream in("a,a,a,1,");
	in >> b;
	assert(b.getAuthor() == "a");
	assert(b.getYear() == 1);
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
	catch (Exception& ex) {
		assert(ex.getMessage().size() != 0);
	}
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
	Repository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "b", "c", 2000);
	try
	{
		serv.add("a", "b", "c", 2000);
	}
	catch (RepositoryException) {}

}

void Tests::testServiceModify()
{
	Repository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "a", "genre", 100);
	serv.modify("a", "a", "aa", "aa", "genre", 200);
	try {
		serv.modify("a", "a", "aa", "aa", "genre", 200);
	}
	catch (Exception&) {}
}

void Tests::testServiceRemove()
{
	Repository<Book> repo{};
	Service serv{ repo };
	try {
		serv.remove("a", "a");
	}
	catch (Exception&) {}
	serv.add("a", "a", "c", 0);
	serv.remove("a", "a");
	assert(serv.getAll().size() == 0);
}

void Tests::testServiceSort()
{
	Repository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("b", "c", "a", 1);
	assert(serv.sortBooks(Book::lessOperatorTitle)[0].getTitle() == "a");
	assert(serv.sortBooks(Book::lessOperatorAuthor)[1].getTitle() == "c");
	assert(serv.sortBooks(Book::lessOperatorGenre)[0].getYear() == 1);
}

void Tests::testServiceFilter()
{
	Repository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("d", "c", "a", 1);
	assert(serv.filter(Book::compareTitle, Book{ "a", "", "", 0 }).size() == 1);
	vector<Book> v = serv.filter(Book::compareYear, Book{ "", "", "", 3 });
	assert(v.size() == 2);
}



/*
void Tests::testLinkedList()
{
	SimplyLinkedList<int> v{};
	v = v;
	assert(v.size() == 0);
	v.push_back(1);
	assert(v.size() == 1);
	assert(v[0] == 1);
	v.push_back(2);
	assert(v[1] == 2);
	assert(v.size() == 2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.erase(4);
	v.erase(3);
	v[0] = 4;
	assert(v[0] == 4);
	assert(v[2] == 3);

	SimplyLinkedList<int> vCopy{ v };
	vCopy = v;
	
	
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
*/

void Tests::testCart()
{
	Repository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("b", "c", "a", 1);
	serv.addToCart("a");
	serv.addToCart("b");
	assert(serv.getCartSize() == 2);
	serv.clearCart();
	assert(serv.getCartSize() == 0);
	serv.generateCart(3);
	assert(serv.getCartSize() == 3);
	vector<Book> v{ serv.getCart() };
	assert(v.size() == 3);
	try
	{
		serv.generateCart(4);
		assert(false);
	}
	catch (RepositoryException&)
	{}
}

void Tests::testUndo()
{
	MapRepository<Book> repo{};
	Service serv{ repo };
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("b", "c", "a", 1);
	serv.modify("a", "a", "A", "A", "a", 11);
	serv.remove("A", "A");
	serv.undo();
	serv.undo();
	serv.undo();
	serv.undo();
	serv.undo();
	try
	{
		serv.undo();
		assert(false);
	}
	catch (Exception& ex)
	{
		assert(ex.getMessage().size() != 0);
	}
}

void Tests::testMapRepository()
{
	MapRepository<int> repo{};
	repo.clearRepository();

	repo.add(1);
	assert(repo.getSize() == 1);
	try
	{
		repo.getElement(-1);
		assert(false);
	}
	catch (Exception&) {}

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
	catch (Exception& ex) {
		assert(ex.getMessage().size() != 0);
	}
	try
	{
		repo.modify(1, 2);
		assert(false);
	}
	catch (RepositoryException& ex) {
		assert(ex.getMessage().size() != 0);
	}
}

void Tests::testFileRepository()
{
	const string& fileName = "test.txt";
	ofstream g(fileName, std::ios::trunc);
	g.close();
	FileRepository<int> repo{ fileName };
	repo.add(1);
	repo.modify(1, 2);
	repo.remove(2);
	assert(repo.getSize() == 0);
}

void Tests::testExport()
{
	const string& fileName = "test.txt";
	ofstream g(fileName, std::ios::trunc);
	g.close();
	FileRepository<Book> repo{"test.txt"};
	Service serv{ repo };
	serv.add("a", "a", "a", 11);
	serv.add("c", "b", "b", 3);
	serv.add("b", "c", "a", 1);
	serv.generateCart(3);
	serv.exportCartToCSV("test.csv");
	try {
		serv.exportCartToCSV("");
	} catch (Exception&) {}
	serv.exportCartToHtml("test.html");
	try {
		serv.exportCartToHtml("");
	} catch (Exception&) {}
}

void Tests::testThrowMapRepository()
{
	int added = 0;
	MapRepository<int> repo{ 0.5 };
	for (int i = 0; i < 10; i++)
	{
		try {
			repo.add(i);
			added++;
		}
		catch (Exception&) {}
	}
	cout << added;
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
	testCart();
	//testLinkedList();
	testUndo();
	testMapRepository();
	testFileRepository();
	testExport();
	testThrowMapRepository();
}