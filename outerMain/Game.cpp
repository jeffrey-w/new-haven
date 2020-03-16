#include "Game.h"
#include "Resources.h"

using std::pair;

Game::Game() : Game(DEFAULT_NUM_PLAYERS) {}

Game::Game(int numPlayers) {
	current = nullptr;
	board = new GBMap(numPlayers);
	resources = new GatherFacility();
	tiles = harvestTileDeck();
	buildings = buildingDeck();
	players = new Roster(numPlayers);
}

void Game::placeShipmentTile() {
	if (!current) {
		throw std::runtime_error("No player at the moment.");
	}
	int type = getInputType();
	pair<int, int> coordinate = getInputCoordinate();
	HarvestTile* shipment = current->getShipmentTile();
	board->calculateResources(coordinate, resources);
	board->setSquare(shipment, coordinate);
	resources->incrementBy(type, HarvestTile::NUM_RESOURCES);
}

std::pair<int, int> Game::getInputCoordinate() {
	return std::pair<int, int>();
}

int Game::getInputType() {
	return 0;
}
