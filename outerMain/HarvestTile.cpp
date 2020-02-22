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
	resources = new vector<ResourceToken*>(*other.resources);
}

HarvestTile::~HarvestTile() {
	delete resources;
}

void HarvestTile::orient(Orientation orientation) {
	ensureNotPlaced(); // TODO document exception
}

void HarvestTile::ensureNotPlaced() {
	for (auto& resource : *resources) {
		if (resource->isPlaced()) {
			throw new std::exception(); // TODO need richer exception type
		}
	}
}

ResourceToken* HarvestTile::tokenize() {
	if (isSpent()) {
		throw new std::exception();
	}
	return (*resources)[(*current)++];
}

void HarvestTile::display() const {
	std::cout << "0";
}
