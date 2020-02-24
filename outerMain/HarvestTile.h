#pragma once

#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"


class HarvestTile : public AbstractPiece {

public:

	constexpr static int NUM_RESOURCES = 4;
	
	HarvestTile();
	HarvestTile(ResourceToken, ResourceToken, ResourceToken, ResourceToken);
	HarvestTile(const HarvestTile&);
	~HarvestTile();
	// Rotates ResourceTokens 90 degrees clockwise the specified number of rotations.
	void rotate(int);
	ResourceToken* tokenize();

private:

	int* current;
	std::vector<ResourceToken*>* resources;

	void ensureNotPlaced();
	
};
