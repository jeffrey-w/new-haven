#include "GBMap.h"
#include "GBMapLoader.h"
#include "VGMap.h"
#include "Player.h"

#include <iostream>

#define ASSERT_THROWS(exception, expression) { \
    try { \
        (expression); \
    } catch (exception& e) { \
        std::cout << "true\n"; \
    } catch (...) { \
        std::cout << "false\n"; \
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
    Building b1;
    Building b2;
    Building b3;
    Building b4;
    Building b5;
    Building b6;
    Building b7;
    Building b8;
    Building b9;
    Building b10;
    vmap.setCircle(&b1, {0,0});
    vmap.setCircle(&b2, {0,1});
    vmap.setCircle(&b3, {0,2});
    vmap.setCircle(&b4, {0,3});
    vmap.setCircle(&b5, {0,4});
    vmap.setCircle(&b6, {1,0});
    vmap.setCircle(&b7, {1,1});
    vmap.setCircle(&b8, {1,2});
    vmap.setCircle(&b9, {1,3});
    vmap.setCircle(&b10,{1,4});
    vmap.display();


    std::cout<<"================================================================================\n";
/*    //TEST PART 3 (Map loaders)
    GBMapLoader loader("map.txt");
    GBMap* loaded = loader.load();
    loaded->display();
    delete loaded;
    loaded = nullptr;
    GBMapLoader loader2("map_bad.txt");
    std::cout << "Invalid number of players caught by GBMapLoader: ";
    ASSERT_THROWS(std::exception, loader2.load());*/

    std::cout<<"================================================================================\n";
    //TEST PART 4 (Player)
    Player p;
    p.buildVillage(&b1, {0,0});
    p.buildVillage(&b2, {1,0});
    p.buildVillage(&b3, {2,0});
    p.buildVillage(&b4, {3,0});
    p.buildVillage(&b5, {4,0});
    p.buildVillage(&b6, {5,0});
    p.buildVillage(&b7, {0,1});
    p.buildVillage(&b8, {0,2});
    p.buildVillage(&b9, {0,3});
    p.buildVillage(&b10, {0,4});
    p.villageBoard->display();
    std::cout<<p.calculateScore()<<std::endl;


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
	map.calculateResources({ 0, 0 }, &gf);

	return 0;
}
