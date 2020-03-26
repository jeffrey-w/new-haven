#include "../maps/VGMap.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "VGMapDriver.h"

void testVGMap() {
	VGMap map;
	Building* b = new Building(BuildingType::MEADOW, 6);
	Building* c = new Building(BuildingType::MEADOW, 6);
	Building* d = new Building(BuildingType::FOREST, 5);
	map.setCircle(b, { 0, 0 });
	d->flip();
	std::cout << "Running VGMap tests:" << std::endl;
	ASSERT_THROWS(std::invalid_argument, map.setCircle(nullptr, { 1, 1 }),
		"ERROR: null building placed.");
	ASSERT_THROWS(std::invalid_argument, map.setCircle(c, { 0, 0 }),
		"ERROR: double placement allowed.");
	ASSERT_THROWS(std::out_of_range, map.setCircle(c, { VGMap::HEIGHT, VGMap::WIDTH }),
		"ERROR: invalid placement allowed.");
	ASSERT_THROWS(std::runtime_error, map.setCircle(c, { 0, 2 }),
		"ERROR invalid placement allowed.");
	ASSERT_THROWS(std::runtime_error, map.setCircle(d, { 0, 1 }),
		"ERROR: invalid placement allowed.");
	std::cout << std::endl;
	delete c, delete d;
}
