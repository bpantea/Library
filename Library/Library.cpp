/**
	Library.cpp file
	The entry point of the app.
*/

#include "ui.h"
#include "tests.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

void start()
{
	Tests tests{};
	tests.run();

	UI ui = UI();
	ui.initializeBooks();
	ui.run();
}

int main()
{
	start();

	_CrtDumpMemoryLeaks();
    return 0;
}