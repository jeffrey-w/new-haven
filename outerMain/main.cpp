#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Controller.h"
#include "test/Drivers.h"

int main() {
	Controller c;
	c.initGame();
	c.inputIDs();
	c.run();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}
