/***************
Building class creates a building given it's type (MEADOW,QUARRY,FOREST,WHEATFIELD) on one side
and number (1-6) on the other side
****************/
#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

class Building
{
public:
	enum Type { MEADOW, QUARRY, FOREST, WHEATFIELD };
	Building(Type, int);  //example: Building myBuilding = Building(Building::WHEATFIELD, 1);
	~Building();
	void printBuilding();
	void flip();

private:
	Type* colour;
	int* number;  //1 to 6
	bool* buildingFaceUp; //the building is face up by default in the constructor, unless flip() is called
};
