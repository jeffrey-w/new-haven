#include <iostream>

#include "loaders/GBMapLoader.h"
#include "loaders/VGMapLoader.h"
#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "Player.h"
#include "test/GBMapDriver.h"
#include "test/MapLoaderDriver.h"
#include "test/VGMapDriver.h"

// TODO delete this
#define ASSERT_THROWS(exception, expression, msg) { \
    try { \
        (expression); \
        std::cerr << msg << std::endl; \
    } catch (exception& e) { \
        std::cerr << e.what() << std::endl; \
    } catch (...) { \
        std::cerr << msg << std::endl; \
    } \
}

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();

    VGMapLoader vloader1("res/vmap.txt");
    VGMap* vloaded = vloader1.load();

    std::cout<<"================================================================================\n";
    // TEST PART 4 (Player)
    Player p;
    for (int i = 0; i < VGMap::WIDTH; i++) {
        Building* b = new Building(BuildingType::QUARRY, 6);
        b->flip();
        p.buildVillage(b, { 0, i });
    }
    for (int i = 1; i < VGMap::HEIGHT; i++) {
        Building* b = new Building(BuildingType::WHEATFIELD, VGMap::HEIGHT - i);
        b->flip();
        p.buildVillage(b, { i, 0 });
    }
    p.getVillageBoard()->display();
    p.calculateScore();


    std::cout<<"================================================================================\n";
    //TEST PART 5 (Deck)





    std::cout<<"================================================================================\n";
    //TEST PART 6 (Scoring facilities)

	GBMap map;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map.setSquare(new HarvestTile(), { i, j });
		}
	}
	GatherFacility gf;
    map.display();
    std::cout << '\n';
	map.calculateResources({ 0, 0 }, &gf); // insert breakpoint here when pulled
    gf.displayCount();

	return 0;
}
