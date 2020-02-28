#pragma once

#include <stack>
#include <vector>

#include "AbstractPiece.h"
#include "Building.h"
#include "HarvestTile.h"

// The base class from which all Decks (i.e. containers for Pieces) shall be derived.
class Deck {

public:
	
	// Constructs a new Deck object.
	Deck();
	// Destroys this Deck.
	~Deck();
	// Removes and returns the Piece at the top of this Deck.
	virtual AbstractPiece* draw() = 0;
	// Returns true iff this Deck has no pieces in it.
	bool empty() const;

protected:

	// Puts the specified Piece on the top of this Deck.
	void push(AbstractPiece*);
	// Removes the Piece at the top of this Deck.
	AbstractPiece* pop();
	// Returns a list view of this Pieces in this Deck.
	std::vector<AbstractPiece*>& asList() const;

private:

	std::stack<AbstractPiece*>* pieces;


};

// The Deck that contains Buildings.
class BuildingDeck : public Deck {

public:

	// Constructs a new BuildingDeck object.
	BuildingDeck();
	// Constructs a new BuildingDeck object that contains copies of the Buildings contained by the
	// specified BuildingDeck.
	BuildingDeck(const BuildingDeck&);
	// Adds the specified Building to this BuildingDeck.
	void add(Building*);
	// Removes and returns the Building at the top of this BuildingDeck.
	Building* draw();

};

// The Deck that contains HarvestTiles.
class HarvestTileDeck : public Deck {

public:

	// Constructs a new HarvestTileDeck object.
	HarvestTileDeck();
	// Constructs a new HarvestTileDeck object that contains copies of the HarvestTiles contained
	// by the specified HarvestTileDeck.
	HarvestTileDeck(const HarvestTileDeck&);
	// Adds the specified HarvestTile to this HarvestTileDeck.
	void add(HarvestTile*);
	// Removes and returns the HarvestTile at the top of this HarvestTileDeck.
	HarvestTile* draw();

};

class Hand {

	void exchange();

private:

	std::vector<HarvestTile*>* tiles;

};
