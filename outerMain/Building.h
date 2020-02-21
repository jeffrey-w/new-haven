/***************
Building class creates a building given it's type (MEADOW,QUARRY,FOREST,WHEATFIELD) on one side
and number (1-6) on the other side
****************/
#pragma once
#include <iostream>
#include <string>

#include "AbstractToken.h"

class Building : public AbstractToken
{
public:
	enum Type { MEADOW, QUARRY, FOREST, WHEATFIELD }; // TODO consider using enum class
	Building();
	Building(Type, int);  //example: Building myBuilding = Building(Building::WHEATFIELD, 1);
	Building(Building& obj);
	~Building();
	/*
	prints building
	*/
	void printBuilding();
	/*
	flips the building
	if the building was faceUp, it becomes face down and vice versa
	*/
	void flip();
	int getNumber();
	bool getFaceUp();
	enum Type getColour();

private:
	const Type* colour;
	const int* number;  //1 to 6
    bool* faceUp; //the building is face up by default in the constructor, unless flip() is called
};
