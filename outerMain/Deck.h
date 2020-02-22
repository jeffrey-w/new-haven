/*
Deck class contains the general pool of harvest tiles and buildings, from which the player can draw from
*/
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
	Deck(const Deck& obj);
	~Deck();
	/*
	This method is called when the player wishes to draw a harvest tile
	The deck "gives away" a harvest tile and removes it from the general pool (harvest tile vector)
	*/
	HarvestTile* giveHarvestTile();  //draw()
	/*
	This method is called when the player wishes to draw a a building
	The deck "gives away" a building and removes it from the general pool (building vector)
	*/
	Building* giveBuilding();   //draw()

private:
	std::vector<HarvestTile*>* harvestTileVector;  //general pool of harvest tiles
	std::vector<Building*>* buildingVector;  //general pool of buildings
	/*
	helper method which generates all buildings stored in the building vector
	*/
	void generateAllBuildings();
	/*
	helper method which randomly generates all harvest tiles stored in the harvest tile vector
	*/
	void generateAllHarvestTiles();
};