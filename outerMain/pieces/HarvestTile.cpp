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

HarvestTile::HarvestTile(const HarvestTile& other) {
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

void HarvestTile::rotate() {
	*current = ++(*current) & NUM_RESOURCES - 1;
}

ResourceToken* HarvestTile::tokenize() {
	ResourceToken* returnToken = (*resources)[*current];
	(*resources)[(*current)++] = nullptr;
	// Avoid an expensive division op.
	*current &= NUM_RESOURCES - 1;
	return returnToken;
}

void HarvestTile::display() const {
	std::cout << *this;
}

void HarvestTile::printHand(std::ostream& stream, const HarvestTile& one, const HarvestTile& two) {
	printHalf(stream, one, *one.current);
	printHalf(stream, two, *two.current);
	// Shipment tile.
	stream << "-- | --\n";
	printHalf(stream, one, *one.current + (NUM_RESOURCES >> 1));
	printHalf(stream, two, *two.current + (NUM_RESOURCES >> 1));
	// Shipment tile.
	stream << "-- | --\n";
}

void HarvestTile::printHalf(std::ostream& stream, const HarvestTile& tile, int from) {
	for (int i = 0; i < NUM_RESOURCES >> 1; i++) {
		stream << *(*tile.resources)[from++];
		from &= NUM_RESOURCES - 1;
		if (i & 1) {
			stream << "\t\t";
		}
		else {
			stream << " | ";
		}
	}
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
