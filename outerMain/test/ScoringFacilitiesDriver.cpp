#include <iostream>
#include <string>

#include "../maps/GBMap.h"
#include "../maps/VGMap.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "ScoringFacilitiesDriver.h"

static void testGatherFacility();
static void testBuildFacility();

void testScoringFacilities() {
	std::cout << "Running scoring facility tests:\n";
	testGatherFacility();
	testBuildFacility();
	std::cout << std::endl;
}

void testGatherFacility() {
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
}

void testBuildFacility() {
	int score;
	VGMap map;
	BuildFacility bf;
	for (int i = 0; i < VGMap::WIDTH; i++) {
		map.setCircle(new Building(BuildingType::FOREST, 1), { 0, i });
	}
	for (int i = 1; i < VGMap::HEIGHT; i++) {
		map.setCircle(new Building(BuildingType::MEADOW, 1), { i, 0 });
	}
	for (int i = 1; i < VGMap::HEIGHT; i++) {
		if (i != 3) {
			Building* b = (i < 3) ? new Building(BuildingType::MEADOW, 1)
				: new Building(BuildingType::QUARRY, 1);
			map.setCircle(b, { i, 1 });
		}
	}
	map.display();
	map.calculateScore(&bf);
	score = bf.getScore();
	ASSERT_EQUALS(11, score, "Successfully calculated VGMap score: " + std::to_string(score) + ".",
		"Miscalculated VGMap score");
}
