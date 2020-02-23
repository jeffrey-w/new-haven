#include "GBMap.h"
#include "VGMap.h"

int main() {
<<<<<<< Updated upstream

    //TEST PART 1 (GBMap)
    GBMap gmap;
    HarvestTile ht1;
    HarvestTile ht2;
    HarvestTile ht3;
    gmap.setSquare(&ht1, {0,0});
    gmap.setSquare(&ht2, {1,0});
    gmap.setSquare(&ht3, {0,1});
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




    //TEST PART 4 (Player)



    //TEST PART 5 (Deck)




    //TEST PART 6 (Scoring facilities)



=======
	GBMap map;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map.setSquare(new HarvestTile(), { i, j });
		}
	}
	map.display();
	GatherFacility gf;
	map.calculateResources({ 0, 0 }, &gf);
>>>>>>> Stashed changes
	return 0;
}
