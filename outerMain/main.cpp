#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

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
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}
