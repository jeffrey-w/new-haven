#include <iostream>

#include "../util/Debug.h"
#include "HarvestTile.h"

using std::vector;

std::string HarvestTile::INVALID_ORIENTATION = "Tile must have an orientation between 0 and "
	+ std::to_string(HarvestTile::NUM_RESOURCES - 1) + ".";

HarvestTile::HarvestTile() : HarvestTile(0) {
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
	if (orientation < 0 || orientation > NUM_RESOURCES - 1) {
		throw std::invalid_argument(INVALID_ORIENTATION);
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

void HarvestTile::printHand(std::ostream& stream, const HarvestTile& one, const HarvestTile& two,
		bool shipment) {
	one.printHalf(stream, *one.current);
	two.printHalf(stream, *two.current);
	if (shipment) {
		stream << "-- | --";
	}
	stream << '\n';
	one.printHalf(stream, (*one.current + NUM_RESOURCES - 1) & NUM_RESOURCES - 1, true);
	two.printHalf(stream, (*two.current + NUM_RESOURCES - 1) & NUM_RESOURCES - 1, true);
	if (shipment) {
		stream << "-- | --";
	}
	stream << '\n';
}

std::ostream& operator<<(std::ostream& stream, const HarvestTile& tile) {
	tile.printHalf(stream, *tile.current);
	tile.printHalf(stream, (*tile.current + HarvestTile::NUM_RESOURCES - 1)
		& HarvestTile::NUM_RESOURCES - 1, true);
	return std::cout << '\n';
}

void HarvestTile::printHalf(std::ostream& stream, int from, bool countdown) const {
	for (int i = 0; i < NUM_RESOURCES >> 1; i++) {
		stream << *(*resources)[from];
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
