#include <iostream>

#include "GameView.h"

GameView::~GameView() {
	delete board;
	delete resources;
	delete pool;
	delete players;
}

void GameView::addStats(Roster* players) {
	stats = new View(players);
}

void GameView::addBoard(GBMap* board) {
	this->board = new View(board);
}

void GameView::addResources(GatherFacility* resources) {
	this->resources = new View(resources);
}

void GameView::addPool(BuildingPool* pool) {
	this->pool = new View(pool);
}

void GameView::addPlayers(Roster* players) {
	this->players = rosterView(players);
}

void GameView::rotate() {
	players->rotate();
}

void GameView::showStats() const {
	std::cout << "Game Stats\n";
	stats->show();
}

void GameView::showBoard() const {
	std::cout << "Game Board\n";
	board->show();
}

void GameView::showResources() const {
	std::cout << "Resources\n";
	resources->show();
}

void GameView::showPool() const {
	std::cout << "Building Pool\n";
	pool->show();
}

void GameView::showTiles() const {
	std::cout << "Harvest Tiles\n";
	players->showTiles();
}

void GameView::showBuildings() const {
	std::cout << "Buildings\n";
	players->showBuildings();
}

void GameView::showVillage() const {
	std::cout << "Village Board\n";
	players->showVillage();
}
