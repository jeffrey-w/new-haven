#include "GameView.h"

GameView::~GameView() {
	delete board;
	delete resources;
	delete pool;
	delete players;
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

void GameView::showBoard() const {
	board->show();
}

void GameView::showResources() const {
	resources->show();
}

void GameView::showPool() const {
	pool->show();
}

void GameView::showTiles() const {
	players->showTiles();
}

void GameView::showBuildings() const {
	players->showBuildings();
}

void GameView::showVillage() const {
	players->showVillage();
}
