#pragma once

#include <deque>
#include <set>

#include "Player.h"

class Roster {

	static constexpr int TILE_HAND_SIZE = 3;

public:

	Roster(int);
	Roster(const Roster&);
	~Roster();
	void deal(Deck<HarvestTile*>*, Deck<Building*>*);
	Player* next();
	void enqueue(Player*); // TODO rename this


private:

	std::set<Player*>* names;
	std::deque<Player*>* players;

	Roster();

};

