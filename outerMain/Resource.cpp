/*************************************************
This class represents resources nodes that constitute the game board
**************************************************/
#include <iostream>
#include <string>
#include "Resource.h"

using std::cout;
using std::cin;
using std::string;

//constructor
Resource::Resource()
{
	type = "";
}

//sets the resource type once the tile is placed onto the board
void Resource::setType(string theType)
{
	type.assign(theType);
}