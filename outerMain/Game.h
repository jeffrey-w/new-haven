#pragma once

#include "maps/GBMap.h"
#include "Player.h"
#include "Roster.h"

// A game of New Haven.
class Game {

public:

	static constexpr int DEFAULT_NUM_PLAYERS = 2;

	Game();
	Game(int);

private:

	Player* current;
	GBMap* board;
	GatherFacility* resources;
	Deck<HarvestTile*>* tiles;
	Deck<Building*>* buildings;
	Roster* players;

	void placeShipmentTile(std::pair<int, int>, int);

};

