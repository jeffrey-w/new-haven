#include "Player.h"
#include "util/Debug.h"

using std::pair;

Player::Player() : Player(new HarvestTile()) {}

Player::Player(HarvestTile* shipment) {
    score = new int(0);
    tiles = new HarvestTileHand(shipment);
    buildings = new BuildingHand();
    village = new VGMap();
}

Player::Player(const Player& other){
    score = new int(*other.score);
    tiles = new HarvestTileHand(*other.tiles);
    buildings = new BuildingHand(*other.buildings);
    village = new VGMap(*other.village);
}

Player::~Player(){
    delete tiles;
    delete buildings;
    delete village;
}

bool Player::canPlay(GatherFacility* resources) {
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        for (int j = 0; j < VGMap::WIDTH; j++) {
            if (village->emptyAt({ i, j })) {
                for (int k = 0; k < buildings->getSize(); k++) {
                    for (int l = 0; l < TokenGraph::NUM_TYPES; l++) {
                        if (buildings->typeOf(k + 1) == l) {
                            if (VGMap::HEIGHT - i == resources->countOf(l)) {
                                if (village->hasType(l)) {
                                    return village->adjacentHolds({ i, j }, l);
                                }
                                else {
                                    return true;
                                }
                            }
                        }
                        else {
                            continue;
                        }
                    }
                }
            }
            else {
                continue;
            }
        }
    }
    return false;
}

int Player::getScore() {
    return *score;
}

void Player::drawBuilding(Deck<Building*>* deck) {
    if (!deck) {
        throw std::invalid_argument("Cannot draw from the null deck.");
    }
    buildings->insert(deck->draw());
}

void Player::drawBuilding(BuildingPool* pool, int selection) {
    buildings->insert(pool->remove(selection));
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
    try {
        village->setCircle(building, circle);
    } catch (const std::exception& e) {
        buildings->insert(building);
        throw e;
    }
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
    *score = village->calculateScore();
}

void Player::rotateTile(int selection) {
    tiles->rotate(selection);
}

void Player::placeTile(int selection, GBMap* map, pair<int, int> square) {
    if (!map) {
        throw std::invalid_argument("Cannot place on the null map.");
    }
    HarvestTile* tile = tiles->select(selection);
    try {
        map->setSquare(tile, square);
    } catch (const std::exception& e) {
        tiles->insert(tile);
        throw e;
    }
}

HarvestTile* Player::reap() {
    return tiles->ship();
}

void Player::store(HarvestTile* tile) {
    tiles->receive(tile);
}

void Player::displayTiles() const {
    std::cout << *tiles;
}

void Player::displayBuildings() const {
    std::cout << *buildings;
}

void Player::displayVillage() const {
    std::cout << *village;
}

int Player::villagers() const {
    return village->buildingCount();
}

int Player::leftOvers() const {
    return buildings->getSize();
}

bool operator<(const Player& one, const Player& two) {
    if (*one.score != *two.score) {
        return *one.score < *two.score;
    }
    if (one.villagers() != two.villagers()) {
        return one.villagers() < two.villagers();
    }
    return two.leftOvers() < one.leftOvers();
}

bool operator==(const Player& one, const Player& two) {
    return *one.score == *two.score && one.villagers() == two.villagers() 
        && one.leftOvers() == two.leftOvers();
}
