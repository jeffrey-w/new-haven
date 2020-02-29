#include "Player.h"

using std::pair;

Player::Player(){
    hand = new Hand();
    villageBoard = new VGMap();
    buildFacility = new BuildFacility();
}

Player::Player(const Player& other){
    hand = new Hand(*other.hand);
    villageBoard = new VGMap(*other.villageBoard);
    buildFacility = new BuildFacility(*other.buildFacility);
}

Player::~Player(){
    delete hand;
    delete villageBoard;
    delete buildFacility;
}

VGMap* Player::getVillageBoard() {
    return villageBoard;
}

Building* Player::drawBuilding(BuildingDeck* deck) {
	return deck->draw(); // TODO document exception
}

void Player::drawHarvestTile(HarvestTileDeck* deck) {
    hand->insert(deck->draw()); // TODO document exception
}

void Player::buildVillage(Building* building, pair<int, int> circle) {
    villageBoard->setCircle(building, circle); // TODO document exception(s)
}

void Player::placeHarvestTile(int selection, GBMap* map, pair<int, int> square) {
    map->setSquare(hand->exchange(selection), square); // TODO document exception(s)
}

void Player::resourceTracker(GatherFacility* resources, int type, int cost) {
    if (resources->countOf(type) < cost) {
        throw std::runtime_error("Not enough resoure.");
    }
    resources->incrementBy(type, -cost);
}

void Player::calculateResources(GBMap* map, pair<int, int> square, GatherFacility* resources) {
	map->calculateResources(square, resources); // TODO document exception
}

void Player::calculateScore() {
    villageBoard->calculateScore(buildFacility); // TODO should only do this once
}