#include "Game.h"
#include "test/Drivers.h"

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();
    testPlayer();
    testResources();
    testScoringFacilities();
    testGameStart();
    return 0;
}
