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
	players = new Roster();
}

Game::~Game() {
	delete board;
	delete resources;
	delete tiles;
	delete buildings;
	delete pool;
	delete players;
}

int Game::numPlayers() const {
	return board->getNumPlayers();
}

size_t Game::tilesLeft() const {
	return tiles->getSize();
}

size_t Game::buildingsLeft() const {
	return buildings->getSize();
}

void Game::addPlayer(uint64_t id) {
	if (atCapacity()) {
		throw std::runtime_error("Too many players.");
	}
	Player* player = new Player();
	try {
		players->add(id, player);
	} catch (const std::invalid_argument& e) {
		delete player;
		throw e;
	}
}

void Game::startGame() {
	if (!atCapacity()) {
		throw std::runtime_error("Too few players.");
	}
	tiles->shuffle();
	buildings->shuffle();
	players->sort();
	pool->replenish(buildings);
	players->deal(tiles, buildings);
}

void Game::rotateTile(int selection) {
	players->next()->rotateTile(selection);
}

bool Game::atCapacity() const {
	return players->getSize() == board->getNumPlayers();
}

void Game::playTile(int selection, pair<int, int> square) { // TODO need to rotate tile
	players->next()->placeHarvestTile(selection, board, square);
	board->calculateResources(square, resources);
	players->jumpQueue();
}

void Game::playShipment(pair<int, int> coordinate, int type) {
	ResourceToken token(static_cast<ResourceType>(type));
	HarvestTile* shipment = players->next()->receiveShipment();
	board->calculateResources(coordinate, resources, &token);
	board->setSquare(shipment, coordinate);
	players->jumpQueue();
}

void Game::playBuilding(int selection, pair<int, int> coordinate) { // TODO need to flip building
	Player* current = players->next();
	current->resourceTracker(resources, current->buildingType(selection),
		valueOfRow(coordinate));
	current->buildVillage(selection, coordinate);
	players->requeue();
}

int Game::valueOfRow(pair<int, int> coordinate) {
	return VGMap::HEIGHT - coordinate.first;
}

void Game::drawBuildingFromDeck() {
	players->next()->drawBuilding(buildings);
	players->jumpQueue();
}

void Game::drawBuildingFromPool(int selection) {
	players->next()->drawBuilding(pool, selection);
	players->jumpQueue();
}

void Game::endTurn() {
	resources->reset();
	pool->replenish(buildings);
	// TODO if not shipment
	players->next()->drawHarvestTile(tiles, false);
	players->requeue();
}

void Game::displayBoard() const {
	board->display();
}

void Game::displayResources() const {
	resources->display();
}

void Game::displayPool() const {
	pool->display();
}

void Game::displayerPlayers() const {
	players->display();
}
