#include "Game.h"
#include "components/Resources.h"

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

Game::Game(const Game& other) {
    board = new GBMap(*other.board);
    if (other.shipment) {
        shipment = new Shipment{new HarvestTile(*other.shipment->payload), other.shipment->coordinate};
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

void Game::addPlayer(long id) {
    if (atCapacity()) {
        throw std::runtime_error("Too many players.");
    }
    Player* player = new Player(tiles->draw());
    try {
        players->add(id, player);
    } catch (const std::invalid_argument& e) {
        tiles->add(player->reap());
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
    resources->notify();
}

void Game::playShipment(pair<int, int> coordinate, int type) {
    ensureSetup();
    ResourceToken token(static_cast<ResourceType>(AbstractToken::validateType(type)));
    HarvestTile* tile = players->peek()->reap();
    try {
        board->calculateResources(coordinate, resources, &token);
        shipment = new Shipment{tile, coordinate};
    } catch (const std::exception& e) {
        players->peek()->store(tile);
        std::rethrow_exception(std::current_exception());
    }
    resources->notify();
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
        std::rethrow_exception(std::current_exception());
    }
    players->notify();
    resources->notify();
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
        players->next();
        board->setSquare(shipment->payload, shipment->coordinate);
        delete shipment;
        shipment = nullptr;
    } else {
        players->next()->drawTile(tiles);
    }
    players->notify();
}

void Game::ensureSetup() {
    if (!atCapacity()) {
        throw std::runtime_error("Game is not ready.");
    }
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
