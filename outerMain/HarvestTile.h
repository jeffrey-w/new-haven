#pragma once

#include <array>
#include <map>

#include "Piece.h"
#include "Resource.h"


class HarvestTile : public Piece {

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
	Resource* next();

private:

	static std::map<Orientation, std::array<int, NUM_RESOURCES>>* ORDER;

	Orientation* orientation;
	std::array<Resource*, NUM_RESOURCES>* resources;

	void ensureNotPlaced();
	
};
