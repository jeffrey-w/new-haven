#include "Player.h"

using std::pair;

void Player::placeHarvestTile(HarvestTile* tile, GBMap* map, pair<int, int> square) {
	map->setSquare(tile, square);
}

Building* Player::drawBuilding(BuildingDeck* deck) {
	return deck->drawAs(); // TODO document exception
}

HarvestTile* Player::drawHarvestTile(HarvestTileDeck* deck) {
	return deck->drawAs(); // TODO document exception
}

void Player::calculateResources(GBMap* map, pair<int, int> square) {
	map->calculateResources(square, gatherFacility); // TODO document exception
}
