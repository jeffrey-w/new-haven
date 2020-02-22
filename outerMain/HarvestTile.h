#pragma once

#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"


class HarvestTile : public AbstractPiece {

public:

	enum class Orientation {
		NORTHWEST,
		SOUTHWEST,
		SOUTHEAST,
		NORTHEAST
	};

	constexpr static int NUM_RESOURCES = 4;
	
	HarvestTile();
	HarvestTile(HarvestTile&);
	~HarvestTile();
	void orient(Orientation);
	ResourceToken* tokenize();

private:

	Orientation* orientation;
	int* current;
	std::vector<ResourceToken*>* resources;

	void ensureNotPlaced();
	int nextIndex();
	
};
