#pragma once

#include "Scanner.h"
#include "VGMap.h"

class VGMapLoader {

public:

	VGMapLoader() = delete;
	VGMapLoader(std::string);
	VGMapLoader(VGMapLoader&) = delete;
	~VGMapLoader();
	VGMap* load();

private:

	Scanner* scanner;

	Building* nextBuilding();
	BuildingToken* nextToken();
	std::pair<int, int> nextCircle();

};

