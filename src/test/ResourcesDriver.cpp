#include <iostream>
#include <string>

#include "../components/Resources.h"
#include "../util/Debug.h"
#include "ResourcesDriver.h"

void testResources() {
	auto tiles = harvestTileDeck();
	auto buildings = buildingDeck();
	std::cout << "Running resource tests:\n";
	std::cout << "Successfully created deck of " + std::to_string(tiles->getSize())
		+ " harvest tiles.\n";
	std::cout << "Successfully created deck of " + std::to_string(buildings->getSize())
		+ " buildings.\n";
	std::cout << std::endl;
	delete tiles, delete buildings;
}
