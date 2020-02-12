/**
Implements HarvestTile class
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "HarvestTile.h"

using std::cout;
using std::cin;
using std::string;

HarvestTile::HarvestTile()
{
	position = new Resource[4];
	buildTile();
}

HarvestTile::~HarvestTile()
{
	delete[] position;
	position = nullptr;
}

void HarvestTile::buildTile()
{
	//srand(time(0));

	int arr[3];
	int randNumber;
	
	//storing a max of 3 different Resources in arr and then putting them in the first 3 positions of the tile
	for (int i = 0; i < 3; i++)
	{
		randNumber = randomIntGenerator(3,0);
		arr[i] = randNumber;
		assignResourceToPosition(randNumber, i);
	}

	//the last position will choose a random arr index
	int randArrayIndex = randomIntGenerator(2, 0);
	int valueAtIndex = arr[randArrayIndex];
	assignResourceToPosition(valueAtIndex, 3);
}

int HarvestTile::randomIntGenerator(int max, int min)
{
	int randNumber = rand() % (max - min + 1) + min;
	return randNumber;
}

void HarvestTile::assignResourceToPosition(int randNumber, int index)
{
	switch (randNumber)
	{
	case 0:
		position[index] = Resource::WHEAT;
		break;
	case 1:
		position[index] = Resource::STONE;
		break;
	case 2:
		position[index] = Resource::TIMBER;
		break;
	case 3:
		position[index] = Resource::SHEEP;
		break;
	default:
		break;
	}
}

void HarvestTile::printTile()
{
	string resArr[] = { "WHEAT", "STONE", "TIMBER", "SHEEP" };
	
	cout << "-----------------------\n";
	cout << "|  " << resArr[position[0]] << "  |  " << resArr[position[1]] << "  |\n";
	cout << "|----------|---------|\n";
	cout << "|  " << resArr[position[3]] << "  |  " << resArr[position[2]] << "  |\n";
	cout << "-----------------------\n";
}

void HarvestTile::changeTileOrientation(int shift)
{ 
	if (shift <= 0 || shift > 3)
	{
		return;
	}

	Resource temp1 = position[1];
	Resource temp2 = position[2];
	Resource temp3 = position[3];

	position[shift % 4] = position[0];
	position[(shift + 1) % 4] = temp1;
	position[(shift + 2) % 4] = temp2;
	position[(shift + 3) % 4] = temp3;
}