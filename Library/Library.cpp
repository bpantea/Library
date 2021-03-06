/**
	Library.cpp file
	The entry point of the app.
*/

#include "ui.h"
#include "tests.h"
//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC

void start()
{
	Tests tests{};
	tests.run();

	//FileRepository<Book> repo{ "books.txt" };
	//Repository<Book> repo;
	MapRepository<Book> repo{ 1 };

	Service serv{ repo };
	UI ui = UI(serv);
	//ui.initializeBooks();
	ui.run();
}

int main()
{
	{
		start();
	}

	//_CrtDumpMemoryLeaks();
    return 0;
}