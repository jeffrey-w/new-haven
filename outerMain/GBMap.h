#pragma once

#include <vector>

#include "Graph.h"
#include "Player.h"

using std::vector;

class GBMap {

public:

	GBMap(int numPlayers);
	bool isConnected(int numPlayers);
	int getConnectedResources();
	//void setSpace(int index, int orientation, Tile tile); TODO need Tile class/maybe richer type for orientation

private:

	Graph* space;
	vector<Player*>* owners ;

};

