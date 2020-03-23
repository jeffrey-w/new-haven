#include "Game.h"
#include "Resources.h"
#include "util/Debug.h"

using std::pair;
using ResourceType = ResourceToken::ResourceType;

Game::Game() : Game(DEFAULT_NUM_PLAYERS) {}

Game::Game(int numPlayers) {
	board = new GBMap(numPlayers);
	resources = new GatherFacility();
	tiles = harvestTileDeck();
	buildings = buildingDeck();
	pool = new BuildingPool();
	current = nullptr;
	players = new Roster(numPlayers);
	tiles->shuffle();
	buildings->shuffle();
	pool->replenish(buildings);
	players->deal(tiles, buildings);
}

Game::~Game() {
	delete board;
	delete tiles;
	delete buildings;
	delete pool;
	delete current;
	delete players;
}

int Game::tilesLeft() const {
	return tiles->getSize();
}

int Game::buildingsLeft() const {
	return buildings->getSize();
}

void Game::displayBoard() const {
	board->display();
}

void Game::displayCount() const {
	resources->display();
}

void Game::displayPool() const {
	pool->display();
}

void Game::displayerPlayers() const {
	players->display();
}

void Game::placeShipmentTile(pair<int, int> coordinate, int type) {
	if (!current) {
		throw std::runtime_error("No player at the moment."); // TODO this belongs in turn()
	}
	ResourceToken token(static_cast<ResourceType>(type));
	HarvestTile* shipment = current->getShipmentTile();
	board->calculateResources(coordinate, resources, &token);
	board->setSquare(shipment, coordinate);
	resources->incrementBy(type, HarvestTile::NUM_RESOURCES);
}
