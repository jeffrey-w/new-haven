#include <iostream>

#include "GameView.h"

using std::string;

GameView::~GameView() {
    delete stats;
    delete board;
    delete resources;
    delete pool;
    delete players;
}

void GameView::addStats(Roster *players) {
    stats = new View(validateObservable(players), new string("Game Stats"));
}

void GameView::addBoard(GBMap *board) {
    this->board = new View(validateObservable(board), new string("Game Board"));
}

void GameView::addResources(GatherFacility *resources) {
    this->resources = new View(validateObservable(resources), new string("Resources"));
}

void GameView::addPool(BuildingPool *pool) {
    this->pool = new View(validateObservable(pool), new string("Building Pool"));
}

void GameView::addPlayers(Roster *players) {
    this->players = rosterView(players);
}

void GameView::rotate() {
    players->rotate();
}

void GameView::showStats(const string *header) const {
    if (stats) {
        stats->show(header);
    }
}

void GameView::showBoard() const {
    if (board) {
        board->show();
    }
}

void GameView::showResources() const {
    if (resources) {
        resources->show();
    }
}

void GameView::showPool() const {
    if (pool) {
        pool->show();
    }
}

void GameView::showTiles() const {
    if (players) {
        players->showTiles();
    }
}

void GameView::showBuildings() const {
    if (players) {
        players->showBuildings();
    }
}

void GameView::showVillage() const {
    if (players) {
        players->showVillage();
    }
}

Observable *GameView::validateObservable(Observable *observable) {
    if (!observable) {
        throw std::invalid_argument("Cannot observe the null subject.");
    }
    return observable;
}
