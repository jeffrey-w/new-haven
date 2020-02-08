#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Deck.h"
#include "HarvestTile.h"
#include "Building.h"

using std::cout;
using std::cin;
using std::vector;

Deck::Deck()
{
	generateAllBuildings();
	generateAllHarvestTiles();
}

void Deck::generateAllBuildings()
{
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			buildingVector.push_back(*new Building(Building::MEADOW, j));
			buildingVector.push_back(*new Building(Building::QUARRY, j));
			buildingVector.push_back(*new Building(Building::FOREST, j));
			buildingVector.push_back(*new Building(Building::WHEATFIELD, j));
		}
	}
}

void Deck::generateAllHarvestTiles()
{
	for (int i = 1; i <= 60; i++)
	{
		harvestTileVector.push_back(*new HarvestTile());
	}
}

Building Deck::giveBuilding()
{
	if (buildingVector.empty())
	{
		cout << "The building deck is empty!\n";
		return;
	}

	srand(time(0));
	int size = buildingVector.size();
	int randNumber = rand() % (size-1 - 0 + 1) + 0;
	Building holder = buildingVector[randNumber];
	
	//removing the building from the vector
	vector<Building>::iterator it;
	it = buildingVector.begin() + randNumber;
	buildingVector.erase(it);
	
	return buildingVector[randNumber];
}

HarvestTile Deck::giveHarvestTile()
{
	if (harvestTileVector.empty())
	{
		cout << "The harvest tile deck is empty!\n";
		return;
	}
	
	HarvestTile holder = harvestTileVector.back();
	harvestTileVector.pop_back();
	return holder;
}