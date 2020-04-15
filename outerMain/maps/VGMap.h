#pragma once

#include <string>

#include "../components/ScoringFacilities.h"
#include "../observers/Observable.h"
#include "../pieces/Building.h"
#include "TokenGraph.h"

// The Board on which Players build their village.
class VGMap : public Observable {

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	// Constructs a new VGMap object.
	VGMap();
	// Constructs a new VGMap object with the same configuration as the specified VGMap.
	VGMap(const VGMap&);
	// Destroys this VGMap.
	~VGMap();
	// Returns true iff no Building occupies this VGMap at the specified circle. Throws an Exception
	// if the specified circle does not reference a circle of this VGMap.
	bool emptyAt(std::pair<int, int>);
	// Returns the number of Buildings on this VGMap.
	int buildingCount() const;
	// Returns true iff this VGMap contains a Building of the specified type.
	bool hasType(int) const;
	// Returns true iff any of the circles of this VGMap that are adjacent to the one at the
	// specified coordinate contain a Building of the specified type. Throws an exception if the
	// specified coordinate does not reference a circle of this VGMap.
	bool adjacentHolds(std::pair<int, int>, int) const;
	// Places the specified Building onto the specified circle of this VGMap. The specified
	// Building is destroyed. Throws an exception if any of the following conditions hold:
	// (1) the specified Building is null,
	// (2) the specified circle is not on this VGMap or it is already occupied,
	// (3) the specified Building is not being placed adjacent to another of the same type, or
	// (4) the specified Building is being played face up on a circle that is not the correct value.
	void setCircle(Building*, std::pair<int, int>);
	// Counts the villagers that have been attracted to this VGMap.
	int calculateScore();

protected:

	std::string* toString() const override;

private:

	TokenGraph* graph;

	static bool valuesMatch(const Building*, int);

	void validatePlacement(const Building*, std::pair<int,int>);
	int countRows();
	int countCols();

};
