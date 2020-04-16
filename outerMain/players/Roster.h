#pragma once

#include <deque>
#include <list>
#include <map>

#include "../views/RosterView.h"
#include "Player.h"

// A collection of New Haven Players.
class Roster {
	
	static constexpr int TILE_HAND_SIZE = 2;

public:

	// Constructs a new Roster object.
	Roster();
	// Constructs a new Roster object with Players possessing the same attributes as those in the
	// specified Roster.
	Roster(const Roster&);
	// Destroys this Roster.
	~Roster();
	// Returns the number of Players in this Roster.
	size_t getSize() const;
	// Returns the ID of the Player at the front of this Roster. Throws an exception if this Roster
	// is empty.
	long nextID() const;
	// Returns the Player in this Roster with the highest score. Throws an exception if this Roster
	// is empty.
	Player max() const;
	// Returns a list of the winning Player(s) IDs. Throws an exception if this Roster is empty.
	std::list<long> winners() const;
	// Adds the specified Player to this Roster with the specified id. Throws an exception if the
	// specified id already belongs to another member of this Roster, or if the specified Player is
	// null.
	void add(long, Player*);
	// Returns the Player at the front of this Roster without removing them from the front. Throws
	// an exception if this Roster is empty.
	Player* peek();
	// Returns the Player at the front of this Roster and removes them from the front. Throws an
	// exception if this Roster is empty.
	Player* next();
	// Sorts the Players in this Roster on the natural ordering of their IDs.
	void sort();
	// Distributes a prescribed number of HarvestTiles and Buildings from the specified Decks to
	// each Player in this Roster. Throws an exception if either of the specified Decks are null.
	void deal(Deck<HarvestTile*>*, Deck<Building*>*);

	friend RosterView* rosterView(Roster*);

private:
	
	std::deque<long>* ids;
	std::map<long, Player*>* players;

	Player* front(bool);

};

