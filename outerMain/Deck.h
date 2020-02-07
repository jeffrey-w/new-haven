#pragma once
#include <iostream>
#include <stack>
#include "HarvestTile.h"
#include "Building.h"

using std::cout;
using std::cin;
using std::stack;

class Deck
{
public:
	Deck();
	void drawBuilding();
	void drawHarvestTile();

private:
	stack<HarvestTile> harvestTileStack;
	stack<Building> buildingStack; //TODO need to make sure the buildings are put in the stack in a randomized order!
	void generateAllBuildings(); //Stores buildings in the stack
	void generateAllHarvestTiles(); //stores harvesttiles in the stack
};