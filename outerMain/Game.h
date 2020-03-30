#pragma once

#include "maps/GBMap.h"
#include "Player.h"
#include "Roster.h"

// A game of New Haven.
class Game {

public:

	static constexpr int DEFAULT_NUM_PLAYERS = 2;

	static int valueOfRow(std::pair<int, int>);

	// Constructs a new Game object.
	Game();
	// Constructs a new Game object with the specified number of Players. Throws an exception if
	// the specified number of players is not between two and four inclusive.
	Game(int);
	// Destroys this Game.
	~Game();
	// Returns the number of Players playing this Game.
	int numPlayers() const;
	// Returns the number of HarvestTiles remaining in this Game's Deck.
	size_t tilesLeft() const;
	// Returns the number of Buildings remaining in this Game's Deck.
	size_t buildingsLeft() const;
	void addPlayer(uint64_t);
	void startGame(); // TODO rename this
	void playTile(int, std::pair<int, int>);
	void playShipment(std::pair<int, int>, int);
	void playBuilding(int, std::pair<int, int>);
	void drawBuildingFromDeck();
	void drawBuildingFromPool(int);
	void endTurn();
	// Writes this Game's GBMap to the standard output stream.
	void displayBoard() const;
	// Writes this Game's resource markers to the standard output stream.
	void displayResources() const;
	// Writes this Game's BuildingPool to the standard output stream.
	void displayPool() const;
	// Writes this Game's Players to the standard ouput stream;
	void displayerPlayers() const;

private:

	GBMap* board;
	GatherFacility* resources;
	Deck<HarvestTile*>* tiles;
	Deck<Building*>* buildings;
	BuildingPool* pool;
	Roster* players;

	bool atCapacity() const;

};

