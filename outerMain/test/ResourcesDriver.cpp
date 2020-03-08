#include <iostream>
#include <string>

#include "../maps/TokenGraph.h"
#include "../Resources.h"
#include "ResourcesDriver.h"

static constexpr int NUM_TILES = 60;
static constexpr int BUILD_BOUND = 6;

static Deck<HarvestTile*> harvestTileDeck();
static Deck<Building*> buildingDeck();

void testResources() {
	auto tiles = harvestTileDeck();
	auto buildings = buildingDeck();
	std::cout << "Running resource tests:\n";
	std::cout << "Successfully created deck of " + std::to_string(tiles.getSize())
		+ " harvest tiles.\n";
	std::cout << "Successfully created deck of " + std::to_string(buildings.getSize())
		+ " buildings.\n";
	std::cout << std::endl;
}

Deck<HarvestTile*> harvestTileDeck() {
	Deck<HarvestTile*> tiles;
	for (int i = 0; i < NUM_TILES; i++) {
		tiles.add(new HarvestTile());
	}
	return tiles;
}

Deck<Building*> buildingDeck() {
	Deck<Building*> buildings;
	for (int i = 0; i < BUILD_BOUND; i++) {
		for (int j = 0; j < BUILD_BOUND; j++) {
			for (int k = 0; k < TokenGraph::NUM_TYPES; k++) {
				BuildingType type = static_cast<BuildingType>(k);
				buildings.add(new Building(type, i + 1));
			}
		}
	}
	return buildings;
}
