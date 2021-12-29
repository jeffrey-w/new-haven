#include <sstream>

#include "HarvestTileHand.h"

using std::string;

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
