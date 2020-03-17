#include "Game.h"
#include "Roster.h"

Roster::Roster(int numPlayers) : Roster() {
	if (numPlayers < Game::DEFAULT_NUM_PLAYERS) {
		throw std::invalid_argument("Must have at least two players.");
	}
	for (int i = 0; i < numPlayers; i++) {
		Player* p = new Player();
		players->push_back(p);
		names->insert(p);
	}
}

Roster::Roster(const Roster& other) : Roster() {
	for (auto& player : *other.players) {
		players->push_back(new Player(*player));
		names->insert(player);
	}
}

Roster::~Roster() {
	for (auto& player : *players) {
		delete player;
	}
	delete names;
	delete players;
}

void Roster::deal(Deck<HarvestTile*>* tiles, Deck<Building*>*buildings) {
	if (!(tiles && buildings)) {
		throw std::invalid_argument("Cannot deal from null deck(s).");
	}
	for (int i = 0; i < 2; i++) {
		for (auto& player : *players) {
			player->drawHarvestTile(tiles);
		}
	}
	for (int i = 0; i < VGMap::HEIGHT; i++) {
		for (auto& player : *players) {
			player->drawBuilding(buildings);
		}
	}
}

Player* Roster::next() {
	Player* player = players->front();
	players->pop_front();
	return player;
}

void Roster::enqueue(Player* player) {
	// Membership in  a Roster is predicated on reference semantics
	if (!names->count(player)) {
		throw std::invalid_argument("Player does not belong to this roster.");
	}
	players->push_back(player);
}

Roster::Roster() {
	names = new std::set<Player*>();
	players = new std::deque<Player*>();
}
