#pragma once

#include "Building.h"

class VGMap {

public:

	static constexpr int HEIGHT = 6, WIDTH = 5;

	VGMap();
	VGMap(VGMap&) = delete; // TODO supress copy constructor?
	~VGMap();
	int costOf(std::pair<int, int>);
	void setCircle(Building*, std::pair<int, int>);

};
