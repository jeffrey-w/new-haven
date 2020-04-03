#pragma once

#include <deque>
#include <map>

#include "Player.h"

class Roster {
	
	static constexpr int TILE_HAND_SIZE = 2;

public:

	Roster();
	Roster(const Roster&);
	~Roster();
	size_t getSize() const;
	long nextID() const;
	void add(long, Player*);
	Player* peek();
	Player* next();
	void sort();
	void deal(Deck<HarvestTile*>*, Deck<Building*>*);
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const Roster&);

private:
	
	std::deque<long>* ids;
	std::map<long, Player*>* players;

	Player* front(bool);

};

