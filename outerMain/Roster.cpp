#include "Roster.h"
#include "util/Debug.h"

using std::deque;
using std::map;

Roster::Roster() {
	ids = new deque<uint64_t>();
	players = new map<uint64_t, Player*>();
}

Roster::Roster(const Roster& other) : Roster() {
	for (auto& id : *other.ids) {
		ids->push_back(id);
	}
	for (auto& entry : *other.players) {
		(*players)[entry.first] = new Player(*entry.second);
	}
}

Roster::~Roster() {
	for (auto& entry : *players) {
		delete entry.second;
	}
	delete ids;
	delete players;
}

size_t Roster::getSize() const {
	return players->size();
}

void Roster::add(uint64_t id, Player* player) {
	if (players->count(id)) {
		throw std::invalid_argument("ID already exists.");
	}
	if (!player) {
		throw std::invalid_argument("Cannot add the null player.");
	}
	ids->push_back(id);
	(*players)[id] = player;
}

Player* Roster::peek() {
	return (*players)[ids->front()];
}

Player* Roster::next() {
	uint64_t id = ids->front();
	ids->pop_front();
	ids->push_back(id);
	return (*players)[id];
}

void Roster::sort() {
	std::sort(ids->begin(), ids->end());
}

void Roster::deal(Deck<HarvestTile*>* tiles, Deck<Building*>* buildings) {
	if (!(tiles && buildings)) {
		throw std::invalid_argument("Cannot deal from null deck(s).");
	}
	for (int i = 0; i < TILE_HAND_SIZE;) {
		bool lastCard = ++i == TILE_HAND_SIZE;
		for (auto& entry : *players) {
			entry.second->drawHarvestTile(tiles, lastCard);
		}
	}
	for (int i = 0; i < VGMap::HEIGHT; i++) {
		for (auto& entry : *players) {
			entry.second->drawBuilding(buildings);
		}
	}
}

void Roster::display() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const Roster& roster) {
	for (auto& entry : *roster.players) {
		stream << "Player ";
		stream << entry.first << "\n\n";
		stream << *entry.second;
	}
	return stream << '\n';
}
