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
private:
	string position[4]; //this array contains the types of the ressources contained in the tile
	// TODO can postion hold for enum types for type saftey/consistency with building?

public:
	//constructor
	HarvestTile();

	void buildTile(); // TODO can this be private?

	//generates a random resource
	//WHEAT
	//STONE
	//TIMBER
	//SHEEP
	string randomResourceGenerator(); // TODO can this be private?

	void printTile();

	//from its current state, all positions are shifted from their current location in a clockwise manner
	//shifts go from 0 to 3, where nothing happens at 0
	//the tile remains shifted until it is shifted again
	void changeTileOrientation(int shift);
};
