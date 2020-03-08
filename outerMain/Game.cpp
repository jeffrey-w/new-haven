#include "Game.h"

using std::deque;

Game::Game() {
	board = new GBMap();
	resources = new GatherFacility();
	tiles = makeTiles();
	buildings = makeBuildings();
	players = new deque<Player*>();
	for (int i = 0; i < GBMap::DEFAULT_NUM_PLAYERS; i++) {
		players->push_back(new Player());
	}
}

Deck<HarvestTile> Game::makeTiles() {
	Deck<HarvestTile> deck;
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
		for (int j = 0; j < HarvestTile::NUM_RESOURCES; j++) {
			if (i != j) {
				for (int k = 0; k < 2; k++) {
					// TODO add new HarvestTile with two i and two j
				}
			}
		}
	}
	return deck;
}

Deck<Building> Game::makeBuildings() {
	return Deck<Building>();
}
