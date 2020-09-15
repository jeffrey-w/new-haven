#include "Player.h"
#include "../views/PlayerView.h"

using std::pair;

Player::Player() : Player(new HarvestTile()) {
}

Player::Player(HarvestTile* shipment) {
    tiles = new HarvestTileHand(shipment);
    buildings = new BuildingHand();
    village = new VGMap();
    score = new BuildFacility();
}

Player::Player(const Player& other) {
    tiles = new HarvestTileHand(*other.tiles);
    buildings = new BuildingHand(*other.buildings);
    village = new VGMap(*other.village);
    score = new BuildFacility(*other.score);
}

Player::~Player() {
    delete tiles;
    delete buildings;
    delete village;
    delete score;
}

bool Player::canPlay(GatherFacility* resources) const {
    int type;
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        for (int j = 0; j < VGMap::WIDTH; j++) {
            if (village->emptyAt({i, j})) {
                // This is theoretically linear in the size of this Player's BuildingHand, however, in practice, that is
                // bound by the constant initial size of the Building Deck being played with.
                for (int k = 0; k < buildings->getSize(); k++) {
                    type = buildings->typeOf(k);
                    if (VGMap::HEIGHT - i <= resources->countOf(type)) {
                        if (village->hasType(type)) {
                            if (village->adjacentHolds({i, j}, type)) {
                                return true;
                            }
                        } else {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int Player::getVillagers() const {
    return score->getVillagers();
}

int Player::getBuilt() const {
    return score->getBuilt();
}

int Player::getUnbuilt() const {
    return score->getUnbuilt();
}

void Player::drawBuilding(Deck<Building*>* deck) {
    if (!deck) {
        throw std::invalid_argument("Cannot draw from the null deck.");
    }
    buildings->insert(deck->draw());
    score->setUnbuilt(buildings->getSize());
}

void Player::drawBuilding(BuildingPool* pool, int selection) {
    buildings->insert(pool->remove(selection));
    score->setUnbuilt(buildings->getSize());
    pool->notify();
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
        std::rethrow_exception(std::current_exception());
    }
    score->setVillagers(village->calculateScore());
    score->setBuilt(village->buildingCount());
    score->setUnbuilt(buildings->getSize());
    buildings->notify();
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

void Player::rotateTile(int selection) {
    tiles->rotate(selection);
    tiles->notify();
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
        std::rethrow_exception(std::current_exception());
    }
}

HarvestTile* Player::reap() {
    return tiles->ship();
}

void Player::store(HarvestTile* tile) {
    tiles->receive(tile);
}

bool Player::operator<(const Player& other) const {
    return *other.score < *score;
}

bool Player::operator==(const Player& other) const {
    return *score == *other.score;
}

PlayerView* playerView(Player* player) {
    return new PlayerView(player->tiles, player->buildings, player->village);
}
