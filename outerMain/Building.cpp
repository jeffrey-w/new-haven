/**
Implementation of Building class
*/
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
	faceUp = new bool(true);
}

Building::Building(Building& obj)
{
	colour = new Type(*obj.colour);
	number = new int(*obj.number);
	faceUp = new bool(*obj.faceUp);
}

Building::~Building()
{
	delete colour;
	colour = nullptr;
	delete number;
	number = nullptr;
	delete faceUp;
	faceUp = nullptr;
}

void Building::printBuilding()
{
	string types[] = { "M", "Q", "F", "W" };

	if (*faceUp)
	{
		cout << types[*colour] << "[U]["<<*number<<"]";
	}
	else
	{
        cout << types[*colour] << "[D]["<<*number<<"]";
	}

}

void Building::flip()
{
	*faceUp = !(*faceUp);
}

int Building::getNumber() {
    return *number;
}

bool Building::getFaceUp() {
    return *faceUp;
}

enum Building::Type Building::getColour() {
    return *colour;
}