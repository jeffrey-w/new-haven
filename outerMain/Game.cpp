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

long Game::nextID() const {
	return players->nextID();
}

bool Game::canPlay() const {
	return players->peek()->canPlay(resources);
}

int Game::exhausted() const {
	int exhausted = 0;
	for (int i = 0; i < TokenGraph::NUM_TYPES; i++) {
		if (!resources->countOf(i)) {
			exhausted++;
		}
	}
	return exhausted;
}

int Game::gameOver() const {
	return board->squaresLeft() == 1;
}

void Game::addPlayer(long id) {
	if (atCapacity()) {
		throw std::runtime_error("Too many players.");
	}
	Player* player = new Player(tiles->draw());
	try {
		players->add(id, player);
	} catch (const std::invalid_argument& e) {
		delete player;
		throw e;
	}
}

void Game::setup() {
	if (!atCapacity()) {
		throw std::runtime_error("Too few players.");
	}
	players->sort();
	pool->replenish(buildings);
	players->deal(tiles, buildings);
}

bool Game::atCapacity() const {
	return players->getSize() == board->getNumPlayers();
}

void Game::rotateTile(int selection) {
	players->peek()->rotateTile(selection);
}

void Game::playTile(int selection, pair<int, int> square) {
	players->peek()->placeTile(selection, board, square);
	board->calculateResources(square, resources);
}

void Game::playShipment(pair<int, int> coordinate, int type) {
	// TODO validate type
	ResourceToken token(static_cast<ResourceType>(type));
	HarvestTile* shipment = players->peek()->receiveShipment();
	board->calculateResources(coordinate, resources, &token);
	board->setSquare(shipment, coordinate);
}

void Game::playBuilding(int selection, pair<int, int> coordinate) {
	Player* current = players->peek();
	current->resourceTracker(resources, current->buildingType(selection),
		VGMap::HEIGHT - coordinate.first);
	current->buildVillage(selection, coordinate);
}

void Game::yield() {
	players->next();
}

void Game::drawFromDeck() {
	players->peek()->drawBuilding(buildings);
}

void Game::drawFromPool(int selection) {
	players->peek()->drawBuilding(pool, selection);
}

void Game::endTurn(bool shipped) {
	resources->reset();
	pool->replenish(buildings);
	if (!shipped) {
		players->next()->drawTile(tiles);
	}
	else {
		players->next();
	}
}

void Game::displayBoard() const {
	board->display();
}

void Game::displayTiles() const {
	players->peek()->displayTiles();
}

void Game::displayVillage() const {
	players->peek()->displayVillage();
}

void Game::displayResources() const {
	resources->display();
}

void Game::displayBuildings() const {
	players->peek()->displayBuildings();
}

void Game::displayPool() const {
	pool->display();
}

void Game::displayerPlayers() const {
	players->display();
}
