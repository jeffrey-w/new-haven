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
	// Constructs a new GBMap object for the specified number of players. Throws an exception if
	// the specified number of players is not between two and four inclusive.
	GBMap(int);
	// Supress copy constructor. Recursively defined data structures require identity semantics.
	GBMap(GBMap&) = delete;
	// Destroys this GBMap.
	~GBMap();
	// Places the specified HarvestTile onto the specified square of this GBMap. Throws an
	// exception if the specified HarvestTile has already been placed; or if the specified square
	// is not on this GBMap or if it is already occupied.
	void setSquare(HarvestTile*, std::pair<int, int>);
	// Counts, starting from the specified square, and records on the specified GatherFacility the
	// number of connected resources of each type on this GBMap.
	void calculateResources(std::pair<int, int>, GatherFacility*);

private:

	int* numPlayers;
	TokenGraph* graph;
	
	void setNumPlayers(int);
	int height();
	int width();
	std::vector<std::pair<int, int>> coordinatesOf(std::pair<int, int>, bool = false);
	std::pair<int, int> expand(int);
	void validateSquare(std::pair<int, int>);
	bool isOnCorner(int, int);

};
