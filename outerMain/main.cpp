#include "GBMap.h"
#include "GBMapLoader.h"
#include "VGMap.h"

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



    //TEST PART 2 (VGmap)
    VGMap vmap;
    Building b1;
    Building b2;
    Building b3;
    vmap.setCircle(&b1, {0,0});
    vmap.setCircle(&b2, {1,0});
    vmap.setCircle(&b3, {0,1});
    vmap.display();



    //TEST PART 3 (Map loaders)
    GBMapLoader loader("map.txt");
    GBMap* loaded = loader.load();
    loaded->display();
    delete loaded;
    loaded = nullptr;


    //TEST PART 4 (Player)



    //TEST PART 5 (Deck)




    //TEST PART 6 (Scoring facilities)




	GBMap map;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map.setSquare(new HarvestTile(), { i, j });
		}
	}
	map.display();
	GatherFacility gf;
	map.calculateResources({ 0, 0 }, &gf);

	return 0;
}
