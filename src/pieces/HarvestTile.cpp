#include <iostream>

#include "HarvestTile.h"
#include "../util/Random.h"

using std::vector;

std::string HarvestTile::INVALID_ORIENTATION =
        "Tile must have an orientation between 0 and " + std::to_string(HarvestTile::NUM_RESOURCES - 1) + ".";

HarvestTile::HarvestTile() : HarvestTile(randomOrientation()) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        // Default constructor returns a random ResourceToken.
        resources->push_back(new ResourceToken());
    }
}

HarvestTile::HarvestTile(ResourceToken* one, ResourceToken* two, ResourceToken* three, ResourceToken* four) :
        HarvestTile(randomOrientation()) {
    resources->push_back(one);
    resources->push_back(two);
    resources->push_back(three);
    resources->push_back(four);
}

HarvestTile::HarvestTile(const HarvestTile& other) {
    current = new int(*other.current);
    resources = new vector<ResourceToken*>();
    for (auto& resource : *other.resources) {
        resources->push_back(new ResourceToken(*resource));
    }
}

HarvestTile::HarvestTile(int orientation) {
    if (orientation < 0 || orientation > NUM_RESOURCES - 1) {
        throw std::invalid_argument(INVALID_ORIENTATION);
    }
    current = new int(orientation);
    resources = new vector<ResourceToken*>();
}

int HarvestTile::randomOrientation() {
    return Random::next(0, NUM_RESOURCES - 1);
}

HarvestTile::~HarvestTile() {
    for (auto& resource : *resources) {
        delete resource;
    }
    delete current;
    delete resources;
}

void HarvestTile::rotate() {
    (*current)++;
}

ResourceToken* HarvestTile::tokenize() {
    // Avoid an expensive division op.
    *current &= NUM_RESOURCES - 1;
    ResourceToken* token = (*resources)[*current];
    (*resources)[(*current)++] = nullptr;
    return token;
}
