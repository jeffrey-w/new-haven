#include <iostream>

#include "loaders/GBMapLoader.h"
#include "loaders/VGMapLoader.h"
#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "Player.h"

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


    //TEST PART 1 (GBMap)
    GBMap gmap;
    // Connectedness.
    std::cout << numberOfNodes(gmap) << std::endl;
    HarvestTile ht1;
    HarvestTile ht2;
    HarvestTile ht3;
    HarvestTile ht4(ht1);
    HarvestTile ht5(ht2);
    HarvestTile ht6(ht3);
    gmap.setSquare(&ht1, {0,0});
    gmap.setSquare(&ht2, {1,0});
    gmap.setSquare(&ht3, {0,1});
    ht4.rotate(1);
    ht5.rotate(2);
    ht6.rotate(3);
    gmap.setSquare(&ht4, {3,3});
    gmap.setSquare(&ht5, {4,3});
    gmap.setSquare(&ht6, {3,4});
    gmap.display();
    // Invalid map.
    ASSERT_THROWS(std::invalid_argument, GBMap(5), "ERROR: invalid number of players allowed.");


    std::cout<<"================================================================================\n";
    //TEST PART 2 (VGmap)
    VGMap vmap;
    for (int i = 0; i < VGMap::WIDTH; i++) {
        vmap.setCircle(new Building(BuildingType::FOREST, 1), { 0, i });
    }
    for (int i = 1; i < VGMap::HEIGHT; i++) {
        vmap.setCircle(new Building(BuildingType::MEADOW, 1), { i, 0 });
    }
    vmap.display();


    std::cout<<"================================================================================\n";
    //TEST PART 3 (Map loaders)
    GBMapLoader gloader1("gmap.txt");
    GBMap* gloaded = gloader1.load();
    gloaded->display();
    delete gloaded;
    gloaded = nullptr;
    GBMapLoader gloader2("gmap_bad.txt");
    ASSERT_THROWS(std::invalid_argument, gloader2.load(), "ERROR: Invalid map read");

    VGMapLoader vloader1("vmap.txt");
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
    std::cout << p.calculateScore() << std::endl;


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
	map.display();
    gf.displayCount();

	return 0;
}
