/*************************************************
This class represents resources nodes that constitute the game board
**************************************************/
#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

class Resource // TODO this isn't needed anymore right?
{
	string type;

	//constructor
	Resource();

	//sets the resource type once the tile is placed onto the board
	void setType(string theType);
};
