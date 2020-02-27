#pragma once

#include <array>

#include "Building.h"
#include "BuildFacilityConcept.h"
#include "TokenGraph.h"

class VGMap {

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	VGMap();
	VGMap(const VGMap&);
	~VGMap();
	void setCircle(Building*, std::pair<int, int>);
	void calculateScore(VillageBuildingScoringFacility*);
	void validateCircle(std::pair<int,int>);
    void display();

private:

    TokenGraph* graph;
    std::array<bool,4>* typePlaced;

	bool valuesMatch(Building*, int);
	int countRows();
	int countCols();

};
