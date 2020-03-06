#include <iostream>

#include "test/Drivers.h"

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();
    runPlayerTests();
    testResources();
    runScoringFacilitiesTests();
	return 0;
}
