#include "Player.h"

void Player::placeHarvestTile(HarvestTile* tile, GBMap* map, std::pair<int, int> square) {
	map->setSquare(square, tile);
}

Building* Player::drawBuilding() {
	if (true) { // TODO !harvestTiles.empty()
		return buildings->giveBuilding();
	}
	throw new std::exception(); // TODO need richer exception type
}

HarvestTile* Player::drawHarvestTile() {
	if (true) {
		return harvestTiles->giveHarvestTile();
	}
	throw new std::exception(); // TODO need richer exception type
}
