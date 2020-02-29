#pragma once

#include "../maps/VGMap.h"
#include "../util/Scanner.h"

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

	std::string errorMessage(std::string);

};

