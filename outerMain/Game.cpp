#include "components/Resources.h"
#include "Game.h"
#include "util/Debug.h"

using std::pair;


Game::Game() : Game(DEFAULT_NUM_PLAYERS) {}

Game::Game(int numPlayers) {
	board = new GBMap(numPlayers);
	shipment = nullptr;
	resources = new GatherFacility();
	tiles = harvestTileDeck();
	buildings = buildingDeck();
	pool = new BuildingPool();
	players = new Roster();
}

Game::~Game() {
	delete board;
	delete shipment;
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
	for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
		if (!resources->countOf(i)) {
			exhausted++;
		}
	}
	return exhausted;
}

int Game::gameOver() const {
	return board->squaresLeft() == 1;
}

std::list<long> Game::winners() const {
	return players->winners();
}

int Game::highscore() const {
	return players->max().getScore();
}

int Game::buidlingsLeft() const {
	return players->max().unbuilt();
}

int Game::buildingsPlayed() const {
	return players->max().built();
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
	if (atCapacity()) {
		setup();
	}
}

bool Game::atCapacity() const {
	return players->getSize() == board->getNumPlayers();
}

void Game::setup() {
	for (auto& square : board->corners()) {
		board->setSquare(tiles->draw(), square);
	}
	pool->replenish(buildings);
	players->sort();
	players->deal(tiles, buildings);
}

void Game::rotateTile(int selection) {
	ensureSetup();
	players->peek()->rotateTile(selection);
}

void Game::playTile(int selection, pair<int, int> square) {
	ensureSetup();
	players->peek()->placeTile(selection, board, square);
	board->calculateResources(square, resources);
}

void Game::playShipment(pair<int, int> coordinate, int type) {
	ensureSetup();
	ResourceToken token(static_cast<ResourceType>(AbstractToken::validateType(type)));
	HarvestTile* tile = players->peek()->reap();
	try {
		board->calculateResources(coordinate, resources, &token);
		shipment = new Shipment{ tile, coordinate };
	} catch (const std::exception& e) {
		players->peek()->store(tile);
		throw e;
	}
}

void Game::playBuilding(int selection, pair<int, int> coordinate) {
	ensureSetup();
	int type, cost = VGMap::HEIGHT - coordinate.first;
	Player* current = players->peek();
	type = current->buildingType(selection);
	current->resourceTracker(resources, type, cost);
	try {
		current->buildVillage(selection, coordinate);
	} catch (const std::exception& e) {
		resources->incrementBy(type, cost);
		throw e;
	}
}

void Game::yield() {
	ensureSetup();
	players->next();
}

void Game::drawFromDeck() {
	ensureSetup();
	players->peek()->drawBuilding(buildings);
}

void Game::drawFromPool(int selection) {
	ensureSetup();
	players->peek()->drawBuilding(pool, selection);
}

void Game::endTurn() {
	ensureSetup();
	resources->reset();
	pool->replenish(buildings);
	if (shipment) {
		board->setSquare(shipment->payload, shipment->coordinate);
		delete shipment;
		shipment = nullptr;
	}
	else {
		players->next()->drawTile(tiles);
	}
}

void Game::ensureSetup() {
	if (!atCapacity()) {
		throw std::runtime_error("Game is not ready.");
	}
}

GameView* gameView(Game* game) {
	GameView* view = new GameView();
	view->addBoard(game->board);
	view->addResources(game->resources);
	view->addPool(game->pool);
	view->addPlayers(game->players);
	return view;
}
