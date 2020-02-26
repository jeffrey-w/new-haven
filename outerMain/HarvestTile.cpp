#include <iostream>

#include "HarvestTile.h"

using std::vector;

<<<<<<< HEAD
HarvestTile::HarvestTile(const HarvestTile& obj)
{
	position = new Resource[4];
	for (int i = 0; i < 4; i++)
	{
		position[i] = obj.position[i];
	}
}

HarvestTile::~HarvestTile()
{
	delete[] position;
	position = nullptr;
=======
HarvestTile::HarvestTile() {
	current = new int(0);
	resources = new vector<ResourceToken*>();
	for (int i = 0; i < NUM_RESOURCES; i++) {
		resources->push_back(new ResourceToken()); // Default constructor returns a random ResourceToken.
	}
>>>>>>> jeff-working
}

HarvestTile::HarvestTile(const HarvestTile& other) : AbstractPiece(other) {
	current = new int(*other.current);
	resources = new vector<ResourceToken*>();
	for (auto& resource : *other.resources) {
		resources->push_back(new ResourceToken(*resource));
	}
}

HarvestTile::~HarvestTile() {
	delete current;
	delete resources;
}

void HarvestTile::rotate(int rotations) {
    ensureNotPlaced();// Prevent mutaion after this harvest tile has already been placed
	*current = (*current - rotations + NUM_RESOURCES) % NUM_RESOURCES;
}

void HarvestTile::ensureNotPlaced() {
	for (auto& resource : *resources) {
		if (resource->isPlaced()) {
			throw std::exception(); // TODO need richer exception type
		}
	}
}

bool HarvestTile::isSpent() const {
	for (auto& resource : *resources) {
		if (!resource->isPlaced()) {
			return false;
		}
	}
	return true;
}

ResourceToken* HarvestTile::tokenize() {
	if (isSpent()) {
		throw std::exception();
	}
	ResourceToken* returnToken = (*resources)[*current];
	*current = ++(*current) % NUM_RESOURCES;
	return returnToken;
}
