#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"

using std::cout;
using std::cin;
using std::string;

class HarvestTile:public GameObject
{
	//-----------------------
	//position0 | position1 |
	//----------|-----------|
	//position3 | position2 |
	//-----------------------
public:
	enum Resource { WHEAT, STONE, TIMBER, SHEEP };
	HarvestTile();
	~HarvestTile();
	void printTile();
	//from its current state, all positions are shifted from their current location in a clockwise manner
	//shifts go from 0 to 3, where nothing happens at 0
	//the tile remains shifted until it is shifted again
	void changeTileOrientation(int shift);

private:
	Resource* position; //this array contains the Resources contained in the tile
	void buildTile();
	int randomIntGenerator(int max, int min);
	void assignResourceToPosition(int randNumber, int index);
};
