#pragma once

#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"


class HarvestTile : public AbstractPiece {

public:

	constexpr static int NUM_RESOURCES = 4;
	
	HarvestTile();
	HarvestTile(HarvestTile&);
	~HarvestTile();
	void rotate(int);
	ResourceToken* tokenize();

private:

	int* current;
	std::vector<ResourceToken*>* resources;

	void ensureNotPlaced();
	
};
