#pragma once

#include <exception>

#include "AbstractPiece.h"
#include "BuildingToken.h"

// The Piece that belong to BuildingDecks and that occupy VGMaps.
class Building : public AbstractPiece {

	friend class VGMapLoader;

public:

	// Constructs a new Building object.
	Building();
	// Constructs a new Building object with the same attributes as the specified Building.
	Building(const Building&);
	// Destroys this Building.
	~Building();
	// Returns the type of this Building.
	int getType() const;
	// Returns true if Building is Face Up
	bool isFaceUp() const;
	// Returns the value of this Building.
	int getValue() const;
	// Returns true iff this Building has been completely tokenized.
	bool isSpent() const;
	// Returns the BuildingToken that constitutes this Building. Throws an exception if this Building has already been tokenized.
	BuildingToken* tokenize();
	// Writes this Building to the standard output stream.

private:

	BuildingToken* token;

};

