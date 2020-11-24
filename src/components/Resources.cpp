#include <sstream>

#include "../maps/TokenGraph.h"
#include "../maps/VGMap.h"
#include "Resources.h"

using std::string;
using std::vector;

HarvestTileHand::HarvestTileHand() : HarvestTileHand(new HarvestTile()) {
}

HarvestTileHand::HarvestTileHand(HarvestTile* shipment) {
    for (int i = 0; i < SIZE; i++) {
        tiles.push_back(nullptr);
    }
    tiles[SIZE - 1] = shipment;
}

HarvestTileHand::HarvestTileHand(const HarvestTileHand& other) {
    for (auto& tile : other.tiles) {
        tiles.push_back(tile ? new HarvestTile(*tile) : nullptr);
    }
}

HarvestTileHand::~HarvestTileHand() {
    for (auto& tile : tiles) {
        delete tile;
    }
}

void HarvestTileHand::insert(HarvestTile* tile) {
    for (int i = 0; i < SIZE - 1; i++) {
        if (!tiles[i]) {
            tiles[i] = tile;
            return;
        }
    }
    throw std::runtime_error("This hand is full.");
}

HarvestTile* HarvestTileHand::select(int selection) {
    return validateSelection(selection, true);
}

void HarvestTileHand::rotate(int selection) {
    validateSelection(selection, false)->rotate();
}

HarvestTile* HarvestTileHand::validateSelection(int selection, bool remove) {
    if (selection < 0 || selection > 1) {
        throw std::invalid_argument("Must select [1]st or [2]nd tile.");
    }
    HarvestTile* tile = tiles[selection];
    if (!tile) {
        throw std::runtime_error("Tile unavailable.");
    }
    if (remove) {
        tiles[selection] = nullptr;
    }
    return tile;
}

bool HarvestTileHand::isEmpty() const {
    return !(tiles[0] || tiles[1]);
}

HarvestTile* HarvestTileHand::ship() {
    if (!tiles[SIZE - 1]) {
        throw std::runtime_error("Shipment tile already played.");
    }
    HarvestTile* tile = tiles[SIZE - 1];
    tiles[SIZE - 1] = nullptr;
    return tile;
}

void HarvestTileHand::receive(HarvestTile* tile) {
    if (tiles[SIZE - 1]) {
        throw std::runtime_error("Shipment already exists.");
    }
    tiles[SIZE - 1] = tile;
}

string HarvestTileHand::toString() const {
    std::ostringstream stream;
    HarvestTile::printTiles(stream, tiles);
    stream << '\n';
    return stream.str();
}

BuildingHand::BuildingHand(const BuildingHand& other) {
    for (auto& building : other.buildings) {
        buildings.push_back(new Building(*building));
    }
}

BuildingHand::~BuildingHand() {
    for (auto& building : buildings) {
        delete building;
    }
}

size_t BuildingHand::getSize() const {
    return buildings.size();
}

void BuildingHand::insert(Building* building) {
    buildings.push_back(building);
    notify();
}

Building* BuildingHand::select(int selection) {
    int index = validateSelection(selection);
    Building* building = buildings[index];
    buildings.erase(buildings.begin() + index);
    return building;
}

int BuildingHand::typeOf(int selection) const {
    return buildings[validateSelection(selection)]->getType();
}

int BuildingHand::validateSelection(int selection) const {
    if (selection < 0 || selection > getSize() - 1) {
        throw std::out_of_range("Selection not in range.");
    }
    return selection;
}

string BuildingHand::toString() const {
    std::ostringstream stream;
    Building::printBuildings(stream, buildings);
    stream << '\n';
    return stream.str();
}

BuildingPool::BuildingPool() {
    for (int i = 0; i < SIZE; i++) {
        buildings.push_back(nullptr);
    }
}

BuildingPool::BuildingPool(const BuildingPool& other) {
    for (auto& building : other.buildings) {
        buildings.push_back(building);
    }
}

BuildingPool::~BuildingPool() {
    for (auto& building : buildings) {
        delete building;
    }
}

size_t BuildingPool::getSize() const {
    return buildings.size();
}

void BuildingPool::replenish(Deck<Building*>* deck) {
    for (int i = 0; i < SIZE; i++) {
        if (deck->isEmpty()) {
            return;
        }
        if (!buildings[i]) {
            buildings[i] = deck->draw();
        }
    }
}

Building* BuildingPool::remove(int selection) {
    Building* result = nullptr;
    if (selection < 0 || selection > SIZE - 1) {
        throw std::out_of_range("Selection not in range.");
    }
    if (!(result = buildings[selection])) {
        throw std::invalid_argument("Building unavailable.");
    }
    buildings[selection] = nullptr;
    return result;
}

string BuildingPool::toString() const {
    std::ostringstream stream;
    Building::printBuildings(stream, buildings);
    stream << '\n';
    return stream.str();
}

Deck<HarvestTile*>* harvestTileDeck() {
    int numTypes = AbstractToken::NUM_TYPES;
    Deck<HarvestTile*>* tiles = new Deck<HarvestTile*>();
    for (int i = 0; i < numTypes; i++) {
        for (int j = 0; j < numTypes; j++) {
            if (i != j) {
                // For each resource type i and each type j, add a new tile with three i and one j.
                tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j))));
                // For each resource type i and each type j, add a new tile with two i and two j.
                tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j))));
            }
        }
    }
    for (int i = 0; i < numTypes; i++) {
        for (int j = 0; j < numTypes; j++) {
            for (int k = 0; k < numTypes; k++) {
                if (!(i == j || i == k || j == k)) {
                    // For each resource type i, each type j, and each type k, add a new tile with two i (on the first
                    // column), one j, and one k.
                    tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                            new ResourceToken(static_cast<ResourceType>(j)),
                            new ResourceToken(static_cast<ResourceType>(i)),
                            new ResourceToken(static_cast<ResourceType>(k))));
                    if (j < k) {
                        // For each resource type i, each type j, and each type k, add a new tile with two i (on the
                        // main diagonal), one j, and one k.
                        tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                                new ResourceToken(static_cast<ResourceType>(j)),
                                new ResourceToken(static_cast<ResourceType>(k)),
                                new ResourceToken(static_cast<ResourceType>(i))));
                    }
                }
            }
        }
    }
    tiles->shuffle();
    return tiles;
}

Deck<Building*>* buildingDeck() {
    Deck<Building*>* buildings = new Deck<Building*>();
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        for (int j = 0; j < VGMap::HEIGHT; j++) {
            for (int k = 0; k < AbstractToken::NUM_TYPES; k++) {
                BuildingType type = static_cast<BuildingType>(k);
                buildings->add(new Building(type, i + 1));
            }
        }
    }
    buildings->shuffle();
    return buildings;
}
