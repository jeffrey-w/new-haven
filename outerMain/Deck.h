#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "HarvestTile.h"
#include "Building.h"

class Deck
{
public:
	Deck();
	HarvestTile* giveHarvestTile();  //draw()
	Building* giveBuilding();   //draw()

private:
	std::vector<HarvestTile*>* harvestTileVector;
	std::vector<Building*>* buildingVector;
	void generateAllBuildings();
	void generateAllHarvestTiles();
};