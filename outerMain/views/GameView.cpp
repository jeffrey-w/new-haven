#include "GameView.h"

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
