#pragma once

#include <deque>
#include <set>

#include "Player.h"

// A collection of New Haven Players.
class Roster {

	static constexpr int TILE_HAND_SIZE = 3;

public:

	// Constructs a new Roster object with the specified number of Players. Throws an exception of
	// the specified number of Players is less than two.
	Roster(int);
	// Constructs a new Roster object with the same attributes as the specified Roster.
	Roster(const Roster&);
	// Destroys this Roster.
	~Roster();
	// Deals a perscribed number of HarvestTiles and Buildings from the specified Decks to each
	// Player in this Roster. Throws an exception if either of the specified Decks is null.
	void deal(Deck<HarvestTile*>*, Deck<Building*>*);
	// Returns the next Player in this Roster to take a turn.
	Player* next();
	// Inserts the specified Player back into this Roster after having taken a turn. Throws an
	// exception if the specified Player does not belong to this Roster.
	void enqueue(Player*);
	// Writes this Roster to the standard output stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const Roster&);


private:

	std::set<Player*>* names;
	std::deque<Player*>* players;

	Roster();

};

