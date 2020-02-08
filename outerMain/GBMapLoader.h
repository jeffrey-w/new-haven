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
	GBMap load();

private:

	std::map<std::pair<int, int>, HarvestTile*>* nodes;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* edges;

	void read(std::ifstream*);
	int getNumPlayers();

};

