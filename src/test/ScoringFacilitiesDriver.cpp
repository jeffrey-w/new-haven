#include <iostream>
#include <string>

#include "../maps/GBMap.h"
#include "../maps/VGMap.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "ScoringFacilitiesDriver.h"

void testScoringFacilities() {
	std::cout << "Running scoring facility tests:\n";
	GBMap map;
	GatherFacility gf;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			map.setSquare(new HarvestTile(), { i, j });
		}
	}
	map.display();
	std::cout << "Counting resources starting from (0, 0):\n";
	map.calculateResources({ 0, 0 }, &gf);
	gf.display();
	std::cout << std::endl;
	std::cout << std::endl;
}
