#pragma once

#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"


class HarvestTile : public AbstractPiece {

	friend class GBMapLoader;

public:

	constexpr static int NUM_RESOURCES = 4;
	
	HarvestTile();
	HarvestTile(const HarvestTile&);
	~HarvestTile();
	// Rotates ResourceTokens 90 degrees clockwise the specified number of rotations.
	void rotate(int);
	// Returns true iff this HarvestTile has been completely tokenized.
	bool isSpent() const;
	ResourceToken* tokenize();

private:

	int* current;
	std::vector<ResourceToken*>* resources;

	void ensureNotPlaced();

};
