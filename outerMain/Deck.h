#pragma once
#include <iostream>
#include <stack>
#include "HarvestTile.h"
#include "Building.h"

using std::cout;
using std::cin;
using std::stack;

class Deck
{
public:
	Deck();
	void drawBuilding();
	void drawHarvestTile();

private:
	stack<HarvestTile> tileStack;
};