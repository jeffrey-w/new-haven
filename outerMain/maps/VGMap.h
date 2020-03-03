#pragma once

#include <array>

#include "../pieces/Building.h"
#include "../ScoringFacilities.h"
#include "TokenGraph.h"

// The Board on which Players build their village.
class VGMap {

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	// Constructs a new VGMap object.
	VGMap();
	// Constructs a new VGMap object with the same configuration as the specified VGMap.
	VGMap(const VGMap&);
	// Destroys this VGMap.
	~VGMap();
	// Places the specified Building onto the specified circle of this VGMap. Throws an exception
	// if any of the following conditions hold:
	// (1) the specified Building is null,
	// (2) the specified circle is not on this VGMap or it is already occupied,
	// (3) the specified Building is not being placed adjacent to another of the same type, or
	// (4) the specified Building is being played face up on a circle that is not the correct value.
	void setCircle(Building*, std::pair<int, int>);
	// Counts the villagers that have been attracted to this VGMap. Throws an exeption if the
	// specified BuildFacility is null.
	void calculateScore(BuildFacility*);
	// Writes this VGMap to the standard output stream.
	void display() const;

private:

    TokenGraph* graph;

	static bool valuesMatch(const Building*, int);

	void validatePlacement(const Building*, std::pair<int,int>);
	int countRows();
	int countCols();

};
