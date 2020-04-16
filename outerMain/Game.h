#pragma once

#include <list>

#include "maps/GBMap.h"
#include "players/Player.h"
#include "players/Roster.h"
#include "views/GameView.h"

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
	// Returns the number of Players playing this Game.
	int numPlayers() const;
	// Returns the ID of the current Player. Throws an exception if this Game has no Players.
	long nextID() const;
	// Returns true iff the current Player is able to build on their VGMap with the resources
	// available. Throws an exception if this Game has no Players.
	bool canPlay() const;
	// Returns the number of resource types that were completely spent during the previous turn of
	// this Game.
	int exhausted() const;
	// Returns true iff this Game's GBMap has only one unoccupied square.
	int gameOver() const;
	// Returns a list of the winning Player(s) IDs. Throws an exception if this Game has no Players.
	std::list<long> winners() const;
	// Returns the score of the winner of this Game. Throws an exception if this Game has no
	// Players.
	int highscore() const;
	// Returns the number of Buildings that the winner of this Game failed to play. Throws an
	// exception if this Game has no Players.
	int buidlingsLeft() const;
	// Returns the number of Buildings the the winner of this Game played. Throws an exception if
	// this Game has no Players.
	int buildingsPlayed() const;
	// Adds a new Player with the specified id to this Game's Roster. Throws an exception if this
	// Game's Roster is already full, or if the specified id is invalid or already taken.
	void addPlayer(long);
	// Rotates the selected HarvestTile in the current Player's HarvestTileHand 90 degrees
	// counterclockwise. Throws an exception if the specified selection is not consistent with the
	// current Player's Hand, or if this Game has not started.
	void rotateTile(int);
	// Induces the current Player to place the selected HarvestTile onto this Game's GBMap at the
	// specified square. Throws an exception if the specified tile selection is not consistent with
	// the current Player's Hand; if the specified square is not on this Game's GBMap or it is
	// already occupied; or if this Game has not started.
	void playTile(int, std::pair<int, int>);
	// Induces the current Player to place their shipment tile onto this Game's GBMap at the
	// specified square. For one turn only, the specified square will contain four of the specified
	// type. Throws an exception if the current Player has already played their shipment tile; if
	// the specified square is not on this Game's GBMap or it is already occupied; the specified
	// type is not a valid ResourceType; or if this Game has not started.
	void playShipment(std::pair<int, int>, int);
	// Induces the current Player to build the selected Building on their VGMap at the specified
	// circle. Throws an exception if any of the following conditions hold:
	// (1) the selected building is not consistent with this Player's hand,
	// (2) the specified circle is not on this Player's VGMap or it is already occupied,
	// (3) the specified Building is not being placed adjacent to another of the same type, or
	// (4) this Game has not started.
	void playBuilding(int, std::pair<int, int>);
	// Induces the current Player to cede the remaining resourers gathered this turn to the other
	// Players of this game. Throws an exception if this Game has not started.
	void yield();
	// Induces the current Player to draw a Building from this Game's Deck. Throws an exception if
	// this Game's Deck is empty, or if this Game has not started.
	void drawFromDeck();
	// Induces the current Player to select a Building from this Game's BuildingPool. Throws an
	// exception if the specified selection is out of range, if it specifies a non-existant
	// building, or if this Game has not started.
	void drawFromPool(int);
	// Resets this Game's resource markers to zero, replenishes its BuildingPool, and induces the
	// current Player to draw a new HarvestTile if they did not just player their shipment tile.
	// Throws an exception if this Game has not started.
	void endTurn();

	friend GameView* gameView(Game*);

private:
	
	struct Shipment {

		HarvestTile* payload;
		std::pair<int, int> coordinate;
	};

	GBMap* board;
	Shipment* shipment;
	GatherFacility* resources;
	Deck<HarvestTile*>* tiles;
	Deck<Building*>* buildings;
	BuildingPool* pool;
	Roster* players;

	bool atCapacity() const;
	void setup();
	void ensureSetup();

};

