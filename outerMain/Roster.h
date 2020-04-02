#pragma once

#include <deque>
#include <map>

#include "Player.h"

class Roster {
	
	static constexpr int TILE_HAND_SIZE = 3;

public:

	Roster();
	Roster(const Roster&);
	~Roster();
	size_t getSize() const;
	void add(uint64_t, Player*);
	Player* peek();
	Player* next();
	void sort();
	void deal(Deck<HarvestTile*>*, Deck<Building*>*);
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const Roster&);

private:
	
	std::deque<uint64_t>* ids;
	std::map<uint64_t, Player*>* players;


};

