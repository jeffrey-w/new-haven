#pragma once

#include <vector>

#include "AbstractMap.h"
#include "HarvestTile.h"

class GBMap : public AbstractMap {

	static constexpr int DEFAULT_NUM_PLAYERS = 2;
	static constexpr int DIM_MIN = 10, DIM_MAX = 14;

public:

	GBMap();
	GBMap(int);
	GBMap(GBMap&) = delete; // Supress copy constructor.
	~GBMap();
	void setSquare(HarvestTile*, std::pair<int, int>);
	void calculateResources(GatherFacility*);

private:

	int* numPlayers;
	std::pair<int, int>* prev;
	
	void setNumPlayers(int);
	int height();
	int width();
	std::vector<std::pair<int, int>> coordinatesOf(std::pair<int, int>);
	std::pair<int, int> expand(int);
	std::pair<int, int> validateSquare(std::pair<int, int>);
	bool isOnCorner(int, int);

};
