#include "HarvestTile.h"

using std::vector;

HarvestTile::HarvestTile() {
	orientation = new Orientation(Orientation::NORTHWEST);
	int curr = static_cast<int>(*orientation);
	resources = new vector<ResourceToken*>(NUM_RESOURCES);
	for (int i = 0; i < NUM_RESOURCES; i++) {
		resources->push_back(new ResourceToken()); // Default constructor returns a random ResourceToken.
	}
}

HarvestTile::HarvestTile(HarvestTile& other) {
	orientation = new Orientation(*other.orientation);
	current = new int(*other.current);
	resources = new vector<ResourceToken*>(*other.resources);
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

ResourceToken* HarvestTile::tokenize() {
	if (isSpent()) {
		throw new std::exception();
	}
	ResourceToken* resource = (*resources)[(*current)++];
	*current = nextIndex();
}
