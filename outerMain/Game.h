#pragma once

#include "maps/GBMap.h"
#include "Player.h"
#include "Roster.h"

// A game of New Haven.
class Game {

public:

	static constexpr int DEFAULT_NUM_PLAYERS = 2;

	// Constructs a new Game object.
	Game();
	// Constructs a new Game object with the specified number of Players. Throws an exception if
	// the specified number of players is not between two and four inclusive.
	Game(int);
	// Destroys this Game.
	~Game();
	// Writes the GBMap that this Game is being played on to the standard output stream.
	void displayBoard() const;

private:

	Player* current;
	GBMap* board;
	GatherFacility* resources;
	Deck<HarvestTile*>* tiles;
	Deck<Building*>* buildings;
	Roster* players;

	void placeShipmentTile(std::pair<int, int>, int);

};

