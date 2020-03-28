#pragma once

#include <exception>

#include "AbstractPiece.h"
#include "BuildingToken.h"

using BuildingType = BuildingToken::BuildingType;

// The Piece that occupies BuildingDecks, BuildingHands, and BuildingPools.
class Building : public AbstractPiece {

	friend class VGMapLoader;

public:

	// Constructs a new Building object.
	Building();
	// Constructs a new Building object with the specifeid type and value. Throws an exception if
	// the specified value is not between one and the Height of a VGMap.
	Building(BuildingType, int);
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
	// Returns the BuildingToken that constitutes this Building.
	BuildingToken* tokenize();
	// Flips this Building. If it was previously face up, it becomes face down and vice versa.
	void flip();
	// Writes this Building to the standard output stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const Building&);

private:

	BuildingToken* token;

};
