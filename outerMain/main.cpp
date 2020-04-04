#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Controller.h"
#include "test/Drivers.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (!std::strcmp("-t", argv[1])) {
            testGBMap();
            testVGMap();
            testGBMapLoader();
            testVGMapLoader();
            testPlayer();
            testResources();
            testScoringFacilities();
        }
        else {
            std::cerr << "Usage: outerMain <-t>\n";
            std::cerr << "t: use this flag to run tests.";
            return 1;
        }
    }
    else {
        Controller c;
        c.initGame();
        c.inputIDs();
        c.run();
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        return 0;
    }
}
