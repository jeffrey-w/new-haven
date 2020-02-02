/***************
Building class creates a building given it's type (MEADOW,QUARRY,FOREST,WHEATFIELD) on one side
and number (1-6) on the other side
****************/
#include <iostream>
#include <string>
#include "Building.h"

using std::cout;
using std::cin;
using std::string;

Building::Building(Type theColour, int theNumber)
{
	colour = new Type(theColour);
	number = new int(theNumber);
	buildingFaceUp = new bool(true);
}

Building::~Building()
{
	delete colour;
	colour = nullptr;
	delete number;
	number = nullptr;
	delete buildingFaceUp;
	buildingFaceUp = nullptr;
}

void Building::printBuilding()
{
	string types[] = { "MEADOW", "QUARRY", "FOREST", "WHEATFIELD" };

	if (*buildingFaceUp)
	{
		cout << "Face up: " << types[*colour] << "\n";
		cout << "Face down: " << *number << "\n";
	}
	else
	{
		cout << "Face up: " << *number << "\n";
		cout << "Face down: " << types[*colour] << "\n";
	}

}

void Building::flip()
{
	*buildingFaceUp = !(*buildingFaceUp);
}