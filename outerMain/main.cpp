#include "GBMap.h"
#include "GBMapLoader.h"
#include "VGMap.h"
#include "Player.h"

#include <iostream>
#include "VGMapLoader.h"

#define ASSERT_THROWS(exception, expression, msg) { \
    try { \
        (expression); \
        std::cout << msg << std::endl; \
    } catch (exception& e) { \
        std::cout << e.what() << std::endl; \
    } catch (...) { \
        std::cout << msg << std::endl; \
    } \
}

int main() {


    //TEST PART 1 (GBMap)
    GBMap gmap;
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
    ASSERT_THROWS(std::invalid_argument, gloader2.load(), "Invalid map read");

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
    p.villageBoard->display();
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
	map.display();
	GatherFacility gf;
	map.calculateResources({ 0, 0 }, &gf); // insert breakpoint here when pulled

	return 0;
}
