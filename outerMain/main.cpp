#include <iostream>

#include "loaders/GBMapLoader.h"
#include "loaders/VGMapLoader.h"
#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "Player.h"
#include "test/GBMapDriver.h"
#include "test/MapLoaderDriver.h"
#include "test/PlayerDriver.h"
#include "test/VGMapDriver.h"

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();
    runPlayerTests();
    //TEST PART 5 (Deck)
    Player p;
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
