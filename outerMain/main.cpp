#include <iostream>

#include "loaders/GBMapLoader.h"
#include "loaders/VGMapLoader.h"
#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "Player.h"


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


    ////TEST PART 1 (GBMap)
    GBMap gmap;
    // Connectedness.
    //std::cout << numberOfNodes(gmap) << std::endl;
    HarvestTile ht1;
    HarvestTile ht2;
    HarvestTile ht3;
    HarvestTile ht4(ht1);
    HarvestTile ht5(ht2);
    HarvestTile ht6(ht3);

    std::cout << "empty map" << std::endl;
    gmap.display();

    ht1.rotate(1);

    std::cout << "placing 0,0 " << std::endl;
    gmap.setSquare(&ht1, {0,0});
    gmap.display();


    std::cout << "placing 1,0 " << std::endl;
    gmap.setSquare(&ht2, {1,0});
    gmap.display();

    std::cout << "placing 0,1 " << std::endl;
    gmap.setSquare(&ht3, {0,1});
    gmap.display();



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
    ////TEST PART 2 (VGmap)
    VGMap vmap;
    for (int i = 0; i < VGMap::WIDTH; i++) {
        vmap.setCircle(new Building(BuildingType::FOREST, 1), { 0, i });
    }
    for (int i = 1; i < VGMap::HEIGHT; i++) {
        vmap.setCircle(new Building(BuildingType::MEADOW, 1), { i, 0 });
    }
    vmap.display();


    std::cout<<"================================================================================\n";
    ////TEST PART 3 (Map loaders)
    GBMapLoader gloader1("res/gmap.txt");
    GBMap* gloaded = gloader1.load();
    gloaded->display();
    delete gloaded;
    gloaded = nullptr;
    GBMapLoader gloader2("res/gmap_bad.txt");
    ASSERT_THROWS(std::invalid_argument, gloader2.load(), "ERROR: Invalid map read.");
    GBMapLoader gloader3("res/gmap_bad_format.txt");
    ASSERT_THROWS(std::runtime_error, gloader3.load(), "ERROR: Read from badly formatted file.")

    VGMapLoader vloader1("res/vmap.txt");
    VGMap* vloaded = vloader1.load();

    std::cout<<"================================================================================\n";
    //// TEST PART 4 (Player)
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
    
    BuildingDeck bDeck;
    std::cout << "size of building Deck is currently: " << bDeck.getSize() << "\n";
    HarvestTileDeck hDeck;
    hDeck.add(new HarvestTile());
    hDeck.add(new HarvestTile());
    hDeck.add(new HarvestTile());
    std::cout << "size of harvest tile Deck is currently: " << hDeck.getSize() << "\n";
    //draw buildings
    for (int i = 0; i < 5; i++) {
        p.drawBuilding(&bDeck);
    }
    std::cout << "after drawing 5 buildings, the size of building Deck is now: " << bDeck.getSize() << "\n";
    //draw harvest tile
    p.drawHarvestTile(&hDeck);
    std::cout << "after drawing 1 harvest tile, the size of harvest tile Deck is now: " << hDeck.getSize() << "\n";
    p.printHarvestTileHand();
    std::cout << "Player currently owns the following Buildings in his hand:\n";
    p.printBuildingHand();

  

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

	//return 0;

}
