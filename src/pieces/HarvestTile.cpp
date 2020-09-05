#include <iostream>

#include "HarvestTile.h"
#include "../util/Random.h"

using std::vector;

HarvestTile::HarvestTile() {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        // Default constructor returns a random ResourceToken.
        resources.push_back(new ResourceToken());
   }
}

HarvestTile::HarvestTile(ResourceToken* one, ResourceToken* two, ResourceToken* three, ResourceToken* four) {
    // Internal represntation: {one, two, four, three}.
    resources.push_back(one);
    resources.push_back(two);
    resources.push_back(four);
    resources.push_back(three);
}

HarvestTile::HarvestTile(const HarvestTile& other) {
    for (auto& resource : other.resources) {
        resources.push_back(new ResourceToken(*resource));
    }
}

HarvestTile::~HarvestTile() {
    for (auto& resource : resources) {
        delete resource;
    }
}

void HarvestTile::rotate() {
    orientation.reorient();
}

ResourceToken* HarvestTile::tokenize() {
    int index = orientation.current();
    ResourceToken* token = resources[index];
    resources[index] = nullptr;
    return token;
}

void HarvestTile::printHand(std::ostream& stream, HarvestTile* one, HarvestTile* two, HarvestTile* shipment) {
    int iters = shipment ? NUM_RESOURCES - 1 : NUM_RESOURCES >> 1;
    bool isRegular; // TODO rename this
    HarvestTile* tile;
    HarvestTile* tiles[NUM_RESOURCES - 1] = {one, two, shipment};
    for (int i = 0; i < iters; i++) {
        stream << "╔════════╤════════╗\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "║        │        ║\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        isRegular = i + 1 < NUM_RESOURCES - 1;
        tile = tiles[i];
        stream << "║   ";
        if (isRegular) {
            stream << *tile->resources[tile->orientation.origin + 0 & NUM_RESOURCES - 1];
        } else {
            stream << "--";
        }
        stream << "   │   ";
        if (isRegular) {
            stream << *tile->resources[tile->orientation.origin + 1 & NUM_RESOURCES - 1];
        } else {
            stream << "--";
        }
        stream << "   ║\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "║        │        ║\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "╟────────┼────────╢\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "║        │        ║\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        isRegular = i + 1 < NUM_RESOURCES - 1;
        tile = tiles[i];
        stream << "║   ";
        if (isRegular) {
            stream << *tile->resources[tile->orientation.origin + 3 & NUM_RESOURCES - 1];
        } else {
            stream << "--";
        }
        stream << "   │   ";
        if (isRegular) {
            stream << *tile->resources[tile->orientation.origin + 2 & NUM_RESOURCES - 1];
        } else {
            stream << "--";
        }
        stream << "   ║\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "║        │       ┌╨┐\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "╚════════╧═══════╡";
        stream << i + 1;
        stream << "│\t";
    }
    stream << '\n';
    for (int i = 0; i < iters; i++) {
        stream << "                 └─┘\t";
    }
    stream << '\n';
}

HarvestTile::Orientation::Orientation() {
    origin = Random::next(0, NUM_RESOURCES - 1);
    pos = 0;
}

void HarvestTile::Orientation::reorient() {
    if (pos) {
        throw std::runtime_error("This tile is already being tokenized.");
    }
    origin++;
}

int HarvestTile::Orientation::current() {
    int current = pos++;
    switch (current) {
    case UPPER_LEFT:
        current = origin;
        break;
    case UPPER_RIGHT:
        current = origin + UPPER_RIGHT;
        break;
    case LOWER_LEFT:
        current = origin + LOWER_RIGHT;
        break;
    case LOWER_RIGHT:
        current = origin + LOWER_LEFT;
        break;
    default:
        throw std::length_error("This tile has already been tokenized.");
    }
    return current & NUM_RESOURCES - 1;
}
