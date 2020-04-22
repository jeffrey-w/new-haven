#include "PlayerView.h"

using std::string;

PlayerView::PlayerView(HarvestTileHand* tiles, BuildingHand* buildings, VGMap* village) {
	if (!(tiles && buildings && village)) {
		throw std::invalid_argument("Cannot observe the null subject.");
	}
	this->tiles = new View(tiles, new string("Tiles"));
	this->buildings = new View(buildings, new string("Buildings"));
	this->village = new View(village, new string("Village Board"));
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
