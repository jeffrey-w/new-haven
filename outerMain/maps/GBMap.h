#pragma once

#include <string>
#include <vector>

#include "../components/ScoringFacilities.h"
#include "../observer/Observable.h"
#include "../pieces/HarvestTile.h"
#include "TokenGraph.h"

// The common board onto which HarvestTiles are placed.
class GBMap : public Observable {

	static constexpr int DIM_MIN = 10, DIM_MAX = 14;
	static constexpr int PLAYERS_MIN = 2, PLAYERS_MAX = 4;
	static std::string INVALID_NUM_PLAYERS;

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
	// Returns the number of Playrs playing on this GBMap.
	int getNumPlayers() const;
	// Returns the coordinates of the corner squares on this GBMap.
	std::vector<std::pair<int, int>> corners() const;
	// Returns the number of unoccupied spaces on this GBMap.
	int squaresLeft() const;
	// Places the specified HarvestTile onto the specified square of this GBMap. The specified
	// HarvestTile is destroyed. Throws an exception if the specified HarvestTile is null; or if
	// the specified square is not on this GBMap or if it is already occupied.
	void setSquare(HarvestTile*, std::pair<int, int>);
	// Counts, starting from the specified square, and records on the specified GatherFacility the
	// number of connected resources of each type on this GBMap. If the specified ResourceToken is
	// not null, then four copies of it will occupy the specified square before counting begins,
	// and then removed afterwards. Throws an exception if the specified square is not on this
	// GBMap.
	void calculateResources(std::pair<int, int>, GatherFacility*, ResourceToken* = nullptr);;
	// Writes this GBMap to the standard output stream.
	void display() const;
	// Writes this GBMap to the standard output stream with four of the specified resource types
	// occupying the specified square. Throws an exception if the specified type is invalid or if
	// the specified square is not on this GBMap.
	void display(int, std::pair<int, int>) const;

	// Returns the number of connected nodes on the graph underlying the specified GBMap.
	friend int numberOfSpaces(GBMap&);
	friend std::ostream& operator<<(std::ostream&, const GBMap&);

private:

	int* numPlayers;
	TokenGraph* graph;
	
	static std::vector<std::pair<int, int>> expand(std::pair<int, int>);
	
	void setNumPlayers(int);
	int height() const;
	int width() const;
	std::vector<std::pair<int, int>> coordinatesOf(std::pair<int, int>, bool = false) const;
	void validateSquare(std::pair<int, int>) const;
	bool isOnCorner(int, int) const;

};
