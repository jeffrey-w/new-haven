#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "HarvestTile.h"

using std::cout;
using std::cin;
using std::string;

//constructor
HarvestTile::HarvestTile()
{
	buildTile();
}

void HarvestTile::buildTile()
{
	srand(time(0));

	string arr[3];
	//storing a max of 3 different resources in arr and then putting them in the tile
	for (int i = 0; i < 3; i++)
	{
		arr[i].assign(randomResourceGenerator());
		position[i].assign(arr[i]);
	}

	//the last position will choose a random arr index
	int randIndex = rand() % (2 - 0 + 1) + 0;

	switch (randIndex)
	{
	case 0:
		position[3].assign(arr[0]);
		break;
	case 1:
		position[3].assign(arr[1]);
		break;
	case 2:
		position[3].assign(arr[2]);
		break;
	default:
		break;
	}
}

//generates a random resource
//WHEAT
//STONE
//TIMBER
//SHEEP
string HarvestTile::randomResourceGenerator()
{
	int randNumber = rand() % (4 - 1 + 1) + 1;
	string resourceType;

	switch (randNumber)
	{
	case 1:
		resourceType.assign("WHEAT");
		break;
	case 2:
		resourceType.assign("STONE");
		break;
	case 3:
		resourceType.assign("TIMBER");
		break;
	case 4:
		resourceType.assign("SHEEP");
		break;
	default:
		break;
	}

	return resourceType;
}

void HarvestTile::printTile()
{
	cout << "-----------------------\n";
	cout << "|  " << position[0] << "  |  " << position[1] << "  |\n";
	cout << "|----------|---------|\n";
	cout << "|  " << position[3] << "  |  " << position[2] << "  |\n";
	cout << "-----------------------\n";
}

//from its current state, all positions are shifted from their current location in a clockwise manner
//shifts go from 0 to 3, where nothing happens at 0
//the tile remains shifted until it is shifted again
void HarvestTile::changeTileOrientation(int shift)
{
	if (shift == 0)
	{
		return;
	}

	string temp1;
	temp1.assign(position[1]);
	string temp2;
	temp2.assign(position[2]);
	string temp3;
	temp3.assign(position[3]);

	position[shift % 4].assign(position[0]);
	position[(shift + 1) % 4].assign(temp1);
	position[(shift + 2) % 4].assign(temp2);
	position[(shift + 3) % 4].assign(temp3);
}