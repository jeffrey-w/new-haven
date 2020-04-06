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

void HarvestTile::printHand(std::ostream& stream, const HarvestTile& one, const HarvestTile& two,
		bool shipment) {
	printHalf(stream, one, *one.current);
	printHalf(stream, two, *two.current);
	if (shipment) {
		stream << "-- | --";
	}
	stream << '\n';
	printHalf(stream, one, (*one.current + NUM_RESOURCES - 1) & NUM_RESOURCES - 1, true);
	printHalf(stream, two, (*two.current + NUM_RESOURCES - 1) & NUM_RESOURCES - 1, true);
	if (shipment) {
		stream << "-- | --";
	}
	stream << '\n';
}

void HarvestTile::printHalf(std::ostream& stream, const HarvestTile& tile, int from,
		bool countdown) {
	for (int i = 0; i < NUM_RESOURCES >> 1; i++) {
		stream << *(*tile.resources)[from];
		if (countdown) {
			from--;
		}
		else {
			from++;
		}
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
	HarvestTile::printHalf(stream, tile, *tile.current);
	HarvestTile::printHalf(stream, tile, (*tile.current + HarvestTile::NUM_RESOURCES - 1)
		& HarvestTile::NUM_RESOURCES - 1, true);
	return std::cout << '\n';
}
