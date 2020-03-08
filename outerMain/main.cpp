#include <iostream>
#include <sstream>
#include <string>

#include "maps/GBMap.h"
#include "test/Drivers.h"

static GBMap* initGBMap();

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();
    testPlayer();
    testResources();
    testScoringFacilities();
    GBMap* map = initGBMap();
    map->display();
    delete map;
	return 0;
}

GBMap* initGBMap() {
    int numPlayers = 0;
    GBMap* map = nullptr;
    do {
        std::cout << "Enter number of players: ";
        std::string input;
        std::getline(std::cin, input);
        std::stringstream(input) >> numPlayers;
        try {
            map = new GBMap(numPlayers);
        } catch (std::invalid_argument & e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Accept default number of players? Y/n: ";
            switch (std::cin.get()) {
            case 'Y':
            case 'y':
                map = new GBMap();
                std::cout << "Creating two player game.\n";
                break;
            case 'N':
            case 'n':
                std::cout << "Okay, try again.\n";
                break;
            default:
                std::cout << "Did not understantd, try again.\n";
            }
            std::cin.ignore();
        }
    } while (!map);
    return map;
}
