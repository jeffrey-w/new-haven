#pragma once

#include <vector>

#include "../maps/TokenGraph.h"
#include "../pieces/HarvestTile.h"
#include "../ScoringFacilities.h"

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
	// Constructs a new GBMap object with the same configuration as the specified GBMap.
	GBMap(const GBMap&);
	// Destroys this GBMap.
	~GBMap();
	// Places the specified HarvestTile onto the specified square of this GBMap. Throws an
	// exception if the specified HarvestTile is null or has already been placed; or if the
	// specified square is not on this GBMap or if it is already occupied.
	void setSquare(HarvestTile*, std::pair<int, int>);
	// Counts, starting from the specified square, and records on the specified GatherFacility the
	// number of connected resources of each type on this GBMap. Throws an exceotion if the
	// specified square is not on this GBMap.
	void calculateResources(std::pair<int, int>, GatherFacility*);
	// Writes this GBMap to the standard output stream.
	void display() const;

	// Returns the number of connected nodes on the graph underlying the specified GBMap.
	friend int numberOfNodes(GBMap&);

private:

	int* numPlayers;
	TokenGraph* graph;
	
	static std::vector<std::pair<int, int>> expand(std::pair<int, int>);
	
	void setNumPlayers(int);
	int height() const;
	int width() const;
	std::vector<std::pair<int, int>> coordinatesOf(std::pair<int, int>, bool = false);
	void validateSquare(std::pair<int, int>);
	bool isOnCorner(int, int);

};
