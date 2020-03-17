#include "Game.h"
#include "Resources.h"

using std::pair;
using ResourceType = ResourceToken::ResourceType;

Game::Game() : Game(DEFAULT_NUM_PLAYERS) {}

Game::Game(int numPlayers) {
	current = nullptr;
	board = new GBMap(numPlayers);
	resources = new GatherFacility();
	tiles = harvestTileDeck();
	buildings = buildingDeck();
	players = new Roster(numPlayers);
}

Game::~Game() {
	delete current;
	delete board;
	delete tiles;
	delete buildings;
	delete players;
}

void Game::displayBoard() const {
	board->display();
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
