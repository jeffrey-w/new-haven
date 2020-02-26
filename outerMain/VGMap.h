#pragma once

#include <array>

#include "Building.h"
#include "TokenGraph.h"

class VGMap {
private:
    TokenGraph* graph;
    std::array<bool,4>* typePlaced;

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	VGMap();
	VGMap(VGMap&) = delete; // TODO supress copy constructor?
	~VGMap();
	void setCircle(Building*, std::pair<int, int>);
	void validateCircle(std::pair<int,int>);
    void display();
};
