#pragma once

#include <fstream>

#include <map>
#include <string>
#include <vector>

#include "GBMap.h"

class GBMapLoader {

public:

	GBMapLoader(std::string path);
	~GBMapLoader();
	GBMap* load();

private:

	int* numPlayers;
	std::map<std::pair<int, int>, HarvestTile*>* nodes;

	void read(std::ifstream*);

};

