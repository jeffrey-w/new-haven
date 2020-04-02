#include "Player.h"
#include "util/Debug.h"

using std::pair;

Player::Player() : Player(new HarvestTile()) {}

Player::Player(HarvestTile* shipment) {
    tiles = new HarvestTileHand(shipment);
    buildings = new BuildingHand();
    villageBoard = new VGMap();
    buildFacility = new BuildFacility();
}

Player::Player(const Player& other){
    tiles = new HarvestTileHand(*other.tiles);
    buildings = new BuildingHand(*other.buildings);
    villageBoard = new VGMap(*other.villageBoard);
    buildFacility = new BuildFacility(*other.buildFacility);
}

Player::~Player(){
    delete tiles;
    delete buildings;
    delete villageBoard;
    delete buildFacility;
}

void Player::drawBuilding(Deck<Building*>* deck) {
    if (!deck) {
        throw std::invalid_argument("Cannot draw from the null deck.");
    }
    buildings->insert(deck->draw());
}

void Player::drawBuilding(BuildingPool* pool, int selection) {
    pool->remove(selection);
}

void Player::drawTile(Deck<HarvestTile*>* deck) {
    if (!deck) {
        throw std::invalid_argument("Cannot draw from the null deck.");
    }
    tiles->insert(deck->draw());
}

void Player::buildVillage(int selection, pair<int, int> circle) {
    Building* building = buildings->select(selection);
    if (building->getValue() == VGMap::HEIGHT - circle.first) {
        if (!building->isFaceUp()) {
            building->flip();
        }
    }
    villageBoard->setCircle(buildings->select(selection), circle);
}

int Player::buildingType(int selection) const {
    return buildings->typeOf(selection);
}

void Player::resourceTracker(GatherFacility* resources, int type, int cost) {
    if (!resources) {
        throw std::invalid_argument("Cannot draw from null resources.");
    }
    if (resources->countOf(type) < cost) {
        throw std::runtime_error("Not enough resoures.");
    }
    resources->incrementBy(type, -cost);
}

void Player::calculateScore() {
    villageBoard->calculateScore(buildFacility); // TODO should only do this once
}

void Player::adjustScore() {
    buildFacility->incrementBy(buildings->worth()); // TODO should only do this once
}

void Player::rotateTile(int selection) {
    tiles->rotate(selection);
}

void Player::placeHarvestTile(int selection, GBMap* map, pair<int, int> square) {
    if (!map) {
        throw std::invalid_argument("Cannot place on the null map.");
    }
    map->setSquare(tiles->select(selection), square);
}

HarvestTile* Player::receiveShipment() {
    return tiles->ship();
}

void Player::display() const {
    std::cout << *this;
}

void Player::displayTiles() const {
    std::cout << *tiles;
}

void Player::displayBuildings() const {
    std::cout << *buildings;
}

void Player::displayVillageBoard() const {
    std::cout << *villageBoard;
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
    stream << *player.tiles;
    stream << '\n';
    stream << *player.buildings;
    stream << '\n';
    stream << *player.villageBoard;
    return stream << '\n';
}
