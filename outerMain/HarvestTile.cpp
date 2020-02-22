#include "HarvestTile.h"

using std::array;
using std::map;

HarvestTile::HarvestTile() {
	orientation = new Orientation(Orientation::NORTHEAST);
	resources = new array<ResourceToken*, NUM_RESOURCES>();
	for (int i = 0; i < NUM_RESOURCES; i++) {
		resources->at(i) = new ResourceToken(); // Default constructor returns a random ResourceToken.
	}
}

HarvestTile::HarvestTile(HarvestTile& other) {
	orientation = new Orientation(*other.orientation);
	resources = new array<ResourceToken*, NUM_RESOURCES>(*other.resources);
}

HarvestTile::~HarvestTile() {
	delete orientation;
	delete resources;
}

void HarvestTile::orient(Orientation orientation) {
	ensureNotPlaced(); // TODO document exception
	this->orientation = new Orientation(orientation);
}

void HarvestTile::ensureNotPlaced() {
	for (auto& resource : *resources) {
		if (resource->isPlaced()) {
			throw new std::exception(); // TODO need richer exception type
		}
	}
}

ResourceToken* HarvestTile::next() {
	return nullptr; // TODO
}
