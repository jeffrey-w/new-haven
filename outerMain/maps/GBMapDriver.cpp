#include "../util/Assert.h"
#include "GBMap.h"

void testGBMap() {
	GBMap one, two(3), three(4);
	one.setSquare(new HarvestTile(), { 0, 0 });
	ASSERT_EQUALS(numberOfNodes(one), 25, "ERROR: two player map is not connected.");
	ASSERT_EQUALS(numberOfNodes(two), 35, "ERROR: three player map is not connected.");
	ASSERT_EQUALS(numberOfNodes(three), 49, "ERROR: four player map is not connected.");
	ASSERT_THROWS(std::invalid_argument, GBMap(5), "ERROR: five player map constructed.");
	ASSERT_THROWS(std::invalid_argument, one.setSquare(new HarvestTile(), { 0, 0 }),
		"ERROR: double placement allowed");
	ASSERT_THROWS(std::invalid_argument, three.setSquare(new HarvestTile(), { 0, 0 }),
		"ERROR: invalid placement allowed.");
}