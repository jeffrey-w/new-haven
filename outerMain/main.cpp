#include <iostream>

#include "loaders/GBMapLoader.h"
#include "loaders/VGMapLoader.h"
#include "maps/GBMap.h"
#include "maps/VGMap.h"
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
