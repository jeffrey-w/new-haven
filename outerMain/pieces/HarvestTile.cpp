#include <iostream>
#include <string>

#include "HarvestTile.h"

using std::vector;

HarvestTile::HarvestTile() {
	current = new int(0);
	resources = new vector<ResourceToken*>();
	for (int i = 0; i < NUM_RESOURCES; i++) {
		// Default constructor returns a random ResourceToken.
		resources->push_back(new ResourceToken());
	}
}

HarvestTile::HarvestTile(ResourceToken* one, ResourceToken* two, ResourceToken* three,
		ResourceToken* four) : HarvestTile(0) {
	resources->push_back(one);
	resources->push_back(two);
	resources->push_back(three);
	resources->push_back(four);
}

HarvestTile::HarvestTile(const HarvestTile& other) : AbstractPiece(other) {
	current = new int(*other.current);
	resources = new vector<ResourceToken*>();
	for (auto& resource : *other.resources) {
		resources->push_back(new ResourceToken(*resource));
	}
}

HarvestTile::HarvestTile(int orientation) {
	if (orientation < 0 || orientation >= NUM_RESOURCES) {
		throw std::invalid_argument("Tile must have an orientation between 0 and 3.");
	}
	current = new int(orientation);
	resources = new vector<ResourceToken*>();
}

HarvestTile::~HarvestTile() {
	delete current;
	delete resources;
}

void HarvestTile::rotate(int rotations) {
	*current = (*current - validateRotation(rotations) + NUM_RESOURCES) % NUM_RESOURCES;
}

int HarvestTile::validateRotation(int rotations) {
	// Avoid applying remainder operator to a negative number.
	if (*current + NUM_RESOURCES < rotations) {
		throw new std::invalid_argument("Cannot rotate " + std::to_string(rotations) + " times.");
	}
	for (auto& resource : *resources) {
		if (resource->isPlaced()) {
			throw std::runtime_error("Cannot rotate tile after placing it.");
		}
	}
	return rotations;
}

bool HarvestTile::isTokenized() const {
	for (auto& resource : *resources) {
		if (!resource->isPlaced()) {
			return false;
		}
	}
	return true;
}

ResourceToken* HarvestTile::tokenize() {
	if (isTokenized()) {
		throw std::runtime_error("This tile has already been placed.");
	}
	ResourceToken* returnToken = (*resources)[*current];
	*current = ++(*current) % NUM_RESOURCES;
	return returnToken;
}

void HarvestTile::display() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const HarvestTile& tile) {
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
		stream << (*tile.resources)[i];
		// i is odd
		if (i & 1) {
			stream << '\n';
		}
		else {
			stream << " | ";
		}
	}
	return std::cout << '\n';
}
