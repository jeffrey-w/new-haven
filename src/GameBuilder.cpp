#include "GameBuilder.h"

GameBuilder::GameBuilder(int numPlayers) {
    this->board = new GBMap(numPlayers);
    tiles = harvestTileDeck();
    buildings = buildingDeck();
    pool = new BuildingPool();
    players = new Roster();
}

int GameBuilder::addPlayer(long id) {
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
    return players->getSize();
}

bool GameBuilder::atCapacity() const {
    return players->getSize() == board->getNumPlayers();
}

void GameBuilder::setup() {
    for (auto& square : board->corners()) {
        board->setSquare(tiles->draw(), square);
    }
    pool->replenish(buildings);
    players->sort();
    players->deal(tiles, buildings);
}

Game* GameBuilder::build() {
    return new Game(board, tiles, buildings, pool, players);
}
