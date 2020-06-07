#include "Controller.h"
#include "test/Drivers.h"

int main() {
	Controller c;
	c.initGame();
	c.inputIDs();
	c.run();
	return 0;
}
