#include "Player.h"

using std::pair;

Player::Player(){
    hHand = new HarvestTileHand();
    bHand = new BuildingHand();
    villageBoard = new VGMap();
    buildFacility = new BuildFacility();
}

Player::Player(const Player& other){
    hHand = new HarvestTileHand(*other.hHand);
    bHand = new BuildingHand(*other.bHand);
    villageBoard = new VGMap(*other.villageBoard);
    buildFacility = new BuildFacility(*other.buildFacility);
}

Player::~Player(){
    delete hHand;
    delete bHand;
    delete villageBoard;
    delete buildFacility;
}

VGMap* Player::getVillageBoard() {
    return villageBoard;
}

void Player::drawBuilding(BuildingDeck* deck) {
    bHand->insert(deck->draw());
}

void Player::drawHarvestTile(HarvestTileDeck* deck) {
    hHand->insert(deck->draw());
}

void Player::buildVillage(Building* building, pair<int, int> circle) {
    villageBoard->setCircle(building, circle);
}

void Player::resourceTracker(GatherFacility* resources, int type, int cost) {
    if (resources->countOf(type) < cost) {
        throw std::runtime_error("Not enough resoures.");
    }
    resources->incrementBy(type, -cost);
}

void Player::calculateScore() {
    villageBoard->calculateScore(buildFacility); // TODO should only do this once
}

void Player::placeHarvestTile(int selection, GBMap* map, pair<int, int> square) {
    map->setSquare(hHand->exchange(selection), square);
}

void Player::calculateResources(GBMap* map, pair<int, int> square, GatherFacility* resources) {
	map->calculateResources(square, resources);
}

void Player::printHarvestTileHand() {
    hHand->display();
}

void Player::printBuildingHand() {
    bHand->display();
}
