/**
creates a harvest tile in the form
-----------------------
position0 | position1 |
----------|-----------|
position3 | position2 |
-----------------------
where each position represent a resource (enum)
*/
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Resource.h"

class HarvestTile
{
public:
	constexpr static int NUM_RESOURCES = 4;
	//enum Resource { WHEAT, STONE, TIMBER, SHEEP };
	HarvestTile();
	~HarvestTile();
	/**
	prints tile
	*/
	void printTile();
	/**
	from its current state, all positions are shifted from their current location in a clockwise manner
	shifts go from 0 to 3, where nothing happens at 0
	the tile remains shifted until it is shifted again
	*/
	void changeTileOrientation(int shift);

	Resource* next();

private:
	Resource* position; //this array contains the Resources (enums) contained in the tile
	/**
	helper method
	called by the constructor to assign each position a ressource randomly
	*/
	void buildTile();
	/**
	helper method
	generates a random integer within specified bounds
	*/
	int randomIntGenerator(int max, int min);
	/**
	helper method
	uses the random number to assign a ressource to position[index]
	*/
	void assignResourceToPosition(int randNumber, int index);
};
