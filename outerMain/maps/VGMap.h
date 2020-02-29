#pragma once

#include <array>

#include "../pieces/Building.h"
#include "../ScoringFacilities.h"
#include "TokenGraph.h"

class VGMap {

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	VGMap();
	VGMap(const VGMap&);
	~VGMap();
	void setCircle(Building*, std::pair<int, int>);
	void calculateScore(BuildFacility*);
    void display();

private:

    TokenGraph* graph;

	void validatePlacement(Building*, std::pair<int,int>);
	bool valuesMatch(Building*, int);
	int countRows();
	int countCols();

};
