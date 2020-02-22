#pragma once

#include <vector>

#include "HarvestTile.h"
#include "TokenGraph.h"
#include "ScoringFacilities.h"

// The common board onto which HarvestTiles are placed.
class GBMap {

	static constexpr int DEFAULT_NUM_PLAYERS = 2;
	static constexpr int DIM_MIN = 10, DIM_MAX = 14;

public:

	// Constructs a new GBMap object.
	GBMap();
	// Constructs a new GBMap object for the specified number of players. Throws an exception if the specified number of players is not between two and four inclusive.
	GBMap(int);
	// Supress copy constructor. Recursively defined data structures require identity semantics.
	GBMap(GBMap&) = delete;
	// Destroys this GBMap.
	~GBMap();
	// Places the specified HarvestTile onto the specified square of this GBMap. Throws an exception if the specified square is not on this GBMap or if it is already occupied.
	void setSquare(HarvestTile*, std::pair<int, int>);
	// Counts and records on the specigied GatherFacility the number of connected resources of each type on this GBMap. Throws an exception if this GBMap is empty.
	void calculateResources(GatherFacility*);

private:

	int* numPlayers;
	TokenGraph* graph;
	std::pair<int, int>* prev;
	
	void setNumPlayers(int);
	int height();
	int width();
	std::vector<std::pair<int, int>> coordinatesOf(std::pair<int, int>);
	std::pair<int, int> expand(int);
	std::pair<int, int> validateSquare(std::pair<int, int>);
	bool isOnCorner(int, int);

};
