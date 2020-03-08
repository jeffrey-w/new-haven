#pragma once

#include <deque>

#include "maps/GBMap.h"
#include "Player.h"

// The top-level class of an instance of New Haven.
class Game {

	Game();
	Game(int);

private:

	static Deck<HarvestTile> makeTiles();
	static Deck<Building> makeBuildings();

	GBMap* board;
	GatherFacility* resources;
	Deck<HarvestTile> tiles;
	Deck<Building> buildings;
	std::deque<Player*>* players; // TODO encapsulate this

};

