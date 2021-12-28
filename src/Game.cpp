#include "Game.h"
#include "components/Resources.h"

using std::pair;

Game::Game(GBMap* board, Deck<HarvestTile*>* tiles, Deck<Building*>* builduings, BuildingPool* pool, Roster* players) {
    this->board = board;
    this->tiles = tiles;
    this->buildings = buildings;
    this->pool = pool;
    this->players = players;
    shipment = nullptr;
    resources = new GatherFacility();
}

Game::Game(const Game& other) {
    board = new GBMap(*other.board);
    if (other.shipment) {
        shipment = new Shipment {new HarvestTile(*other.shipment->payload), other.shipment->coordinate};
    } else {
        shipment = nullptr;
    }
    resources = new GatherFacility(*other.resources);
    tiles = new Deck<HarvestTile*>(*other.tiles);
    buildings = new Deck<Building*>(*other.buildings);
    pool = new BuildingPool(*other.pool);
    players = new Roster(*other.players);
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
    return players->getSize();
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

bool Game::gameOver() const {
    return board->squaresLeft() == 1;
}

void Game::rotateTile(int selection) {
    players->peek()->rotateTile(selection);
}

void Game::playTile(int selection, pair<int, int> square) {
    players->peek()->placeTile(selection, board, square);
    board->calculateResources(square, resources);
    resources->notify();
}

void Game::playShipment(pair<int, int> coordinate, int type) {
    ResourceToken token(static_cast<ResourceType>(AbstractToken::validateType(type)));
    HarvestTile* tile = players->peek()->reap();
    try {
        board->calculateResources(coordinate, resources, &token);
        shipment = new Shipment {tile, coordinate};
    } catch (const std::exception& e) {
        players->peek()->store(tile);
        throw;
    }
    resources->notify();
}

void Game::playBuilding(int selection, pair<int, int> coordinate) {
    int type, cost = VGMap::HEIGHT - coordinate.first;
    Player* current = players->peek();
    type = current->buildingType(selection);
    current->resourceTracker(resources, type, cost);
    try {
        current->buildVillage(selection, coordinate);
    } catch (const std::exception& e) {
        resources->incrementBy(type, cost);
        throw;
    }
    players->notify();
    resources->notify();
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

void Game::endTurn() {
    resources->reset();
    pool->replenish(buildings);
    if (shipment) {
        players->next();
        board->setSquare(shipment->payload, shipment->coordinate);
        delete shipment;
        shipment = nullptr;
    } else {
        players->next()->drawTile(tiles);
    }
    players->notify();
}

GameView* gameView(Game* game) {
    GameView* view = new GameView();
    view->addStats(game->players);
    view->addBoard(game->board);
    view->addResources(game->resources);
    view->addPool(game->pool);
    view->addPlayers(game->players);
    return view;
}
