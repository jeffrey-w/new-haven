#include "Player.h"
#include "util/Debug.h"

using std::pair;

Player::Player() : Player(new HarvestTile()) {}

Player::Player(HarvestTile* shipment) {
    tiles = new HarvestTileHand(shipment);
    buildings = new BuildingHand();
    village = new VGMap();
    score = new BuildFacility();
}

Player::Player(const Player& other){
    tiles = new HarvestTileHand(*other.tiles);
    buildings = new BuildingHand(*other.buildings);
    village = new VGMap(*other.village);
    score = new BuildFacility(*other.score);
}

Player::~Player(){
    delete tiles;
    delete buildings;
    delete village;
    delete score;
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
    village->calculateScore(score); // TODO should only do this once
}

void Player::adjustScore() {
    score->incrementBy(buildings->worth()); // TODO should only do this once
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
