#pragma once

#include "AbstractToken.h"

/***************
Building class creates a building given it's type (MEADOW,QUARRY,FOREST,WHEATFIELD) on one side
and number (1-6) on the other side
****************/
class BuildingToken : public AbstractToken {

public:

	enum class BuildingType { 
		MEADOW,
		QUARRY,
		FOREST,
		WHEATFIELD
	};
	
	BuildingToken();
	BuildingToken(BuildingType, int);  //example: Building myBuilding = Building(Building::WHEATFIELD, 1);
	BuildingToken(BuildingToken&);
	~BuildingToken();
	bool getFaceUp() const;
	int getType() const;
	int getValue() const;
	/*
	flips the building
	if the building was faceUp, it becomes face down and vice versa
	*/
	void flip();
	void display() const;

private:

	BuildingType* type;
	int* value;  //1 to 6
    bool* faceUp; //the building is face up by default in the constructor, unless flip() is called

	int validateValue(int);
	BuildingType randomType();
	int randomValue();

};
