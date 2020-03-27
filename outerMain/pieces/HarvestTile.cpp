#include <iostream>
#include <string>

#include "../util/Debug.h"
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
	for (auto& resource : *resources) {
		delete resource;
	}
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
	return rotations;
}

ResourceToken* HarvestTile::tokenize() {
	ResourceToken* returnToken = (*resources)[*current];
	(*resources)[(*current)++] = nullptr;
	*current &= NUM_RESOURCES - 1;
	return returnToken;
}

void HarvestTile::display() const {
	std::cout << *this;
}

std::ostream& HarvestTile::printHand(std::ostream& stream, const HarvestTile& one, 
		const HarvestTile& two, const HarvestTile& shipment) {
	printTop(stream, one);
	printTop(stream, two);
	printTop(stream, shipment);
	stream << '\n';
	printBottom(stream, one);
	printBottom(stream, two);
	printBottom(stream, shipment);
	return stream << '\n';
}

std::ostream& HarvestTile::printTop(std::ostream& stream, const HarvestTile&tile) {
	int limit = NUM_RESOURCES >> 1, index = *tile.current;
	for (int i = 0; i < limit; i++) {
		stream << *(*tile.resources)[index++];
		index &= NUM_RESOURCES - 1;
		if (i & 1) {
			stream << "\t\t";
		}
		else {
			stream << " | ";
		}
	}
	return stream;
}

std::ostream& HarvestTile::printBottom(std::ostream& stream, const HarvestTile& tile) {
	int limit = NUM_RESOURCES >> 1, index = *tile.current + limit;
	for (int i = 0; i < limit; i++) {
		stream << *(*tile.resources)[index++];
		index &= NUM_RESOURCES - 1;
		if (i & 1) {
			stream << "\t\t";
		}
		else {
			stream << " | ";
		}
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const HarvestTile& tile) {
	int index = *tile.current;
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
		stream << *(*tile.resources)[index++];
		index &= HarvestTile::NUM_RESOURCES - 1;
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
