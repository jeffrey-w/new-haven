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

void GameView::addStats(Roster* players) {
	stats = new View(validateObservable(players));
}

void GameView::addBoard(GBMap* board) {
	this->board = new View(validateObservable(board));
}

void GameView::addResources(GatherFacility* resources) {
	this->resources = new View(validateObservable(resources));
}

void GameView::addPool(BuildingPool* pool) {
	this->pool = new View(validateObservable(pool));
}

void GameView::addPlayers(Roster* players) {
	this->players = rosterView(players);
}

void GameView::rotate() {
	players->rotate();
}

void GameView::showStats(const string& header) const {
	if (stats) {
		std::cout << header << '\n';
		stats->show();
	}
}

void GameView::showBoard() const {
	if (board) {
		std::cout << "Game Board\n";
		board->show();
	}
}

void GameView::showResources() const {
	if (resources) {
		std::cout << "Resources\n";
		resources->show();
	}
}

void GameView::showPool() const {
	if (pool) {
		std::cout << "Building Pool\n";
		pool->show();
	}
}

void GameView::showTiles() const {
	if (players) {
		std::cout << "Harvest Tiles\n";
		players->showTiles();
	}
}

void GameView::showBuildings() const {
	if (players) {
		std::cout << "Buildings\n";
		players->showBuildings();
	}
}

void GameView::showVillage() const {
	if (players) {
		std::cout << "Village Board\n";
		players->showVillage();
	}
}

Observable* GameView::validateObservable(Observable* observable) {
	if (!observable) {
		throw std::invalid_argument("Cannot observe the null subject.");
	}
	return observable;
}
