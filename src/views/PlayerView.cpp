#include "PlayerView.h"

using std::string;

PlayerView::PlayerView(HarvestTileHand* tiles, BuildingHand* buildings, VGMap* village) {
    this->tiles = new View(tiles, "Tiles");
    this->buildings = new View(buildings, "Buildings");
    this->village = new View(village, "Village Board");
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
