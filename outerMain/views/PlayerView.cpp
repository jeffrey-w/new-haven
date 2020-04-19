#include "PlayerView.h"

PlayerView::PlayerView(HarvestTileHand* tiles, BuildingHand* buildings, VGMap* village) {
	if (!(tiles && buildings && village)) {
		throw std::invalid_argument("Cannot observe the null subject.");
	}
	this->tiles = new View(tiles);
	this->buildings = new View(buildings);
	this->village = new View(village);
}

PlayerView::~PlayerView() {
	delete tiles;
	delete buildings;
	delete village;
}

void PlayerView::showTiles() const {
	tiles->show();
}

void PlayerView::showBuildings() const {
	buildings->show();
}

void PlayerView::showVillage() const {
	village->show();
}
