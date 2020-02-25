#include "Player.h"

using std::pair;

Player::Player(){
    villageBoard = new VGMap;
    gatherFacility = new GatherFacility;
    buildFacility = new BuildFacility;
}

Player::Player(const Player& other){
    //villageBoard=new VGMap(*other.villageBoard);//TODO consider how must behave with VGmap having no copy constructor
    villageBoard=other.villageBoard; //TODO for now shallow, consider fixing it
    gatherFacility = new GatherFacility(*other.gatherFacility);
    buildFacility = new BuildFacility(*other.buildFacility);
}

Player::~Player(){
    delete villageBoard;
    delete gatherFacility;
    delete buildFacility;
}

Building* Player::drawBuilding(BuildingDeck* deck) {
	return deck->drawAs(); // TODO document exception
}

HarvestTile* Player::drawHarvestTile(HarvestTileDeck* deck) {
	return deck->drawAs(); // TODO document exception
}

void Player::buildVillage(Building* building, bool faceDown, std::pair<int, int> circle) {
    villageBoard->setCircle(building, faceDown, circle);
    int index=circle.first * villageBoard->WIDTH + circle.second;//calculates associated index in buildFacility
    buildFacility->markOccupied(index);
    if(faceDown){buildFacility->markFaceDown(index);}
}

void Player::placeHarvestTile(HarvestTile* tile, GBMap* map, pair<int, int> square) {
    map->setSquare(tile, square);
}

void Player::calculateResources(GBMap* map, pair<int, int> square) {
	map->calculateResources(square, gatherFacility); // TODO document exception
}

int Player::calculateScore() {
    return buildFacility->getScore();
}