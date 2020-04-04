#pragma once

#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"

using ResourceType = ResourceToken::ResourceType;

// The Piece that occupies HarvestTileDecks and HarvesTileHands.
class HarvestTile : public AbstractPiece {

	friend class GBMapLoader;

public:

	// The number of resources that a HarvestTile holds.
	constexpr static int NUM_RESOURCES = 4;

	static void printHand(std::ostream&, const HarvestTile&, const HarvestTile&, bool);
	
	// Constructs a new HarvestTile object.
	HarvestTile();
	// Constructs a new HarvestTile object containing the specified ResourceTokens.
	HarvestTile(ResourceToken*, ResourceToken*, ResourceToken*, ResourceToken*);
	// Constructs a new HarvestTile object with the same resources and configuration as the
	// specified HarvestTile.
	HarvestTile(const HarvestTile&);
	// Destroys this HarvestTile.
	~HarvestTile();
	// Rotates this HarvestTile 90 degrees counterclockwise.
	void rotate();
	// Iteratively returns the ResourceTokens that constitute this HarvestTile.
	ResourceToken* tokenize();
	// Writes this HarvestTile to the standard output stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const HarvestTile&);

private:

	int* current;
	std::vector<ResourceToken*>* resources;

	static void printHalf(std::ostream&, const HarvestTile&, int, bool = false);

	// For GBMapLoader.
	HarvestTile(int);

};
