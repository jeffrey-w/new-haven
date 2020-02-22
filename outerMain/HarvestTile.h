#pragma once

#include <array>
#include <map>

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
	ResourceToken* next();

private:

	Orientation* orientation;
	std::array<ResourceToken*, NUM_RESOURCES>* resources;

	void ensureNotPlaced();
	
};
