#include "ui.h"

void UI::printMenu() const
{
	cout << '\n';
	cout << "1. Add book. \n";
	cout << "2. Print all books. \n";
	cout << "3. Modify a book. \n";
	cout << "4. Remove a book. \n";
	cout << "5. Filter by title. \n";
	cout << "6. Filter by year. \n";
	cout << "7. Sort by title. \n";
	cout << "8. Sort by author. \n";
	cout << "9. Sort by genre + year. \n";
	cout << "10. Add book to cart. \n";
	cout << "11. Free cart. \n";
	cout << "12. Generate cart. \n";
	cout << "13. Print cart. \n";
	cout << "14. Undo. \n";
	cout << "15. Export to html. \n";
	cout << "16. Export to cvs. \n";
	cout << "0. Exit. \n";
	cout << '\n';
}

void UI::addUI()
{
	string title, author, genre;
	int year;
	cout << "Title: ";
	getline(cin, title);
	cout << "Author: ";
	getline(cin, author);
	cout << "Genre: ";
	getline(cin, genre);
	cout << "Publishing year: ";
	cin >> year;
	service.add(title, author, genre, year);
}

void UI::printAllElemsUI()
{
	cout << '\n';
	for (const auto& book : service.getAll())
		printBook(book);
	cout << '\n';
}

void UI::printBook(const Book& b) const
{
	cout << b.getTitle() << ':' << b.getAuthor() << ':' << b.getGenre() << ' ' << b.getYear() << '\n';
}

void UI::modifyBook()
{
	string title, author, genre, oldTitle, oldAuthor;
	int year;
	cout << "Old title: ";
	getline(cin, oldTitle);
	cout << "Old author ";
	getline(cin, oldAuthor);
	cout << "Title: ";
	getline(cin, title);
	cout << "Author: ";
	getline(cin, author);
	cout << "Genre: ";
	getline(cin, genre);
	cout << "Publishing year: ";
	cin >> year;
	service.modify(oldTitle, oldAuthor, title, author, genre, year);
}

void UI::removeBook()
{
	string title, author;
	cout << "Title: ";
	getline(cin, title);
	cout << "Author: ";
	getline(cin, author);
	
	service.remove(title, author);
}

void UI::filterTitle()
{
	cout << "Title: ";
	string title;
	cin >> title;
	Book bt{ title, "", "", 0 };
	for (const auto& b : service.filter(Book::compareTitle, bt))
		printBook(b);
	cout << '\n';
}

void UI::filterYear()
{
	cout << "Publishing year: ";
	int year;
	cin >> year;
	Book by{ "", "", "", year };
	for (const auto& b : service.filter(Book::compareYear, by))
		printBook(b);
}

void UI::sortTitle()
{
	for (const auto& b : service.sortBooks(Book::lessOperatorTitle))
		printBook(b);
	cout << '\n';
}

void UI::sortAuthor()
{
	for (const auto& b : service.sortBooks(Book::lessOperatorAuthor))
		printBook(b);
	cout << '\n';
}

void UI::sortGenre()
{
	for (const auto& b : service.sortBooks(Book::lessOperatorGenre))
		printBook(b);
	cout << '\n';
}

void UI::addToCart()
{
	string title;
	cout << "Title: ";
	getline(cin, title);
	service.addToCart(title);
}

void UI::clearCart()
{
	service.clearCart();
}

void UI::randomFillCart()
{
	int size;
	cout << "Size: ";
	cin >> size;
	service.generateCart(size);
}

void UI::printCart()
{
	cout << '\n';
	for (const auto& b : service.getCart())
		printBook(b);
	cout << '\n';
}

void UI::initializeBooks()
{
	service.add("Moara cu noroc", "Ioan Slavici", "nuvela", 1880);
	service.add("Luceafarul", "Eminescu", "poezie", 1881);
	service.add("Maitreyi", "Eliade", "roman", 1933);
}

void UI::exportHtml()
{
	string fileName;
	cout << "File name: ";
	cin >> fileName;
	service.exportCartToHtml(fileName);
}

void UI::exportCvs()
{
	string fileName;
	cout << "File name: ";
	cin >> fileName;
	service.exportCartToCSV(fileName);
}

void UI::run()
{
	while (true)
	{
		printMenu();
		int command;
		cin >> command;
		cin.get();
		try
		{
			if (command == 0)
				return;
			if (command == 1)
				addUI();
			if (command == 2)
				printAllElemsUI();
			if (command == 3)
				modifyBook();
			if (command == 4)
				removeBook();
			if (command == 5)
				filterTitle();
			if (command == 6)
				filterYear();
			if (command == 7)
				sortTitle();
			if (command == 8)
				sortAuthor();
			if (command == 9)
				sortGenre();
			if (command == 10)
				addToCart();
			if (command == 11)
				clearCart();
			if (command == 12)
				randomFillCart();
			if (command == 13)
				printCart();
			if (command == 14)
				undo();
			if (command == 15)
				exportHtml();
			if (command == 16)
				exportCvs();
		}
		catch (Exception& ex) {
			cout << '\n' << ex.getMessage() << '\n';
		}
	}
}