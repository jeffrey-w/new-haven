#pragma once

#include "GBMap.h"
#include "Scanner.h"

class GBMapLoader {

public:

	GBMapLoader() = delete;
	GBMapLoader(std::string);
	GBMapLoader(GBMapLoader&) = delete;
	~GBMapLoader();
	GBMap* load();

private:

	Scanner* scanner;

	int getNumPlayers();
	HarvestTile* nextTile();
	ResourceToken* nextToken();
	std::pair<int, int> nextSquare();

};
