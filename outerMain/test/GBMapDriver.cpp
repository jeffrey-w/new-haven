#include <string>

#include "../maps/GBMap.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "GBMapDriver.h"

using std::string;

static constexpr int MIN_NODES = 25, MID_NODES = 35, MAX_NODES = 49;

static string intro(const int, const string&);
static string success(const int);
static string failure(const string&);

void testGBMap() {
	GBMap one, two(3), three(4);
	HarvestTile* tile = new HarvestTile();
	one.setSquare(new HarvestTile(), { 0, 0 });
	std::cout << "Running GBMap tests:" << std::endl;
	std::cout << intro(MIN_NODES, "two");
	ASSERT_EQUALS(numberOfSpaces(one), MIN_NODES, success(MIN_NODES), failure("two"));
	std::cout << intro(MID_NODES, "three");
	ASSERT_EQUALS(numberOfSpaces(two), MID_NODES, success(MID_NODES), failure("three"));
	std::cout << intro(MAX_NODES, "four");
	ASSERT_EQUALS(numberOfSpaces(three), MAX_NODES, success(MAX_NODES), failure("four"));
	ASSERT_THROWS(std::invalid_argument, GBMap(5),
		"ERROR: five player map constructed.");
	ASSERT_THROWS(std::invalid_argument, one.setSquare(nullptr, { 0, 1 }),
		"ERROR: null tile placed.");
	ASSERT_THROWS(std::invalid_argument, one.setSquare(tile, { 0, 0 }),
		"ERROR: double placement allowed");
	ASSERT_THROWS(std::invalid_argument, three.setSquare(tile, { 0, 0 }),
		"ERROR: invalid placement allowed.");
	std::cout << std::endl;
	delete tile;
}

string intro(const int nodes, const string& players) {
	return "Expect " + std::to_string(nodes) + " nodes on a " + players + " player board: ";
}

string success(const int nodes) {
	return "Counted " + std::to_string(nodes) + " nodes.";
}

string failure(const string& players) {
	return "ERROR: " + players + " player map is not connected.";
}
