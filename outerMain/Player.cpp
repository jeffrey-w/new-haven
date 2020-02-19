#include "Player.h"

void Player::placeHarvestTile(HarvestTile* tile, GBMap* map, std::pair<int, int> square) {
	map->setSquare(square, tile);
}

Building* Player::drawBuilding(BuildingDeck* deck) {
	return deck->drawAs(); // TODO throws exception
}

HarvestTile* Player::drawHarvestTile(HarvestTileDeck* deck) {
	return deck->drawAs(); // TODO throws exception
}
