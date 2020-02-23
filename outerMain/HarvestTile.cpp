#include <iostream>

#include "HarvestTile.h"

using std::vector;

HarvestTile::HarvestTile() {
	current = new int(0);
	resources = new vector<ResourceToken*>();
	for (int i = 0; i < NUM_RESOURCES; i++) {
		resources->push_back(new ResourceToken()); // Default constructor returns a random ResourceToken.
	}
}

HarvestTile::HarvestTile(HarvestTile& other) {
	current = new int(*other.current);
	resources = new vector<ResourceToken*>();
	for (auto& resource : *other.resources) {
		resources->push_back(new ResourceToken(*resource));
	}
}

HarvestTile::~HarvestTile() {
	delete resources;
}

void HarvestTile::rotate(int rotations) {
    ensureNotPlaced();// Prevent mutaion after this harvest tile has already been placed
	*current = (*current - rotations + NUM_RESOURCES) % NUM_RESOURCES;
}

void HarvestTile::ensureNotPlaced() {
	for (auto& resource : *resources) {
		if (resource->isPlaced()) {
			throw new std::exception(); // TODO need richer exception type
		}
	}
}

ResourceToken* HarvestTile::tokenize() {
	static int count = 0;
	if (isSpent()) {
		throw new std::exception();
	}
	if (++count == NUM_RESOURCES) {
		spend(); // Prevent the same HarvestTile from being tokenized twice.
	}
	ResourceToken* returnToken = (*resources)[*current];
	*current = ++(*current) % NUM_RESOURCES;
	return returnToken;
}
