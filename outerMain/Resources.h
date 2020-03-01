#pragma once

#include <vector>

#include "pieces/AbstractPiece.h"
#include "pieces/Building.h"
#include "pieces/HarvestTile.h"

// The base class from which all Decks (i.e. containers for Pieces) shall be derived.
class Deck {

public:
	
	// Constructs a new Deck object.
	Deck();
	// Destroys this Deck.
	~Deck();
	// Returns true iff this Deck has no pieces in it.
	bool empty() const;
	// Returns the number of elements in this Deck
	int getSize();
	// Removes and returns the Piece at the top of this Deck.
	virtual AbstractPiece* draw() = 0;

protected:

	// Puts the specified Piece on the top of this Deck.
	void push(AbstractPiece*);
	// Removes the Piece at the top of this Deck.
	AbstractPiece* pop();
	// Returns a list view of this Pieces in this Deck.
	std::vector<AbstractPiece*>& asList() const;

private:

	std::vector<AbstractPiece*>* pieces;

};

// The Deck that contains Buildings.
class BuildingDeck : public Deck {

public:

	// Constructs a new BuildingDeck object.
	BuildingDeck();
	// Constructs a new BuildingDeck object that contains copies of the Buildings contained by the
	// specified BuildingDeck.
	BuildingDeck(const BuildingDeck&);
	// Adds the specified Building to this BuildingDeck. Throws an exception if the specified
	// Building is null.
	void add(Building*);
	// Removes and returns the Building at the top of this BuildingDeck. Throws an exception if
	// this BuildingDeck is empty.
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
	// Adds the specified HarvestTile to this HarvestTileDeck. Throws an exception if the specified
	// HavestTile is null.
	void add(HarvestTile*);
	// Removes and returns the HarvestTile at the top of this HarvestTileDeck. Throws an exception if
	// this HarvestTileDeck is empty.
	HarvestTile* draw();

};

// The collection of HarvestTiles owned by a Player.
class HarvestTileHand {

public:

	// Constructs a new HarvestTileHand object.
	HarvestTileHand();
	// Contstruts a new HarvestTileHand object with the specified shipment tile.
	HarvestTileHand(HarvestTile*);
	// Constructs a new HarvestTileHand object with the same contents as the specified Hand.
	HarvestTileHand(const HarvestTileHand&);
	// Destroys this HarvestTileHand.
	~HarvestTileHand();
	// Adds the specified HarvestTile to this HarvestTileHand. Throws an exception if this HarvestTileHand is full.
	void insert(HarvestTile*);
	// Returns the HarvestTile selected by a Player. Throws an exception if the specified selection
	// is not between one and two inclusive.
	HarvestTile* exchange(int);
	// Return this HarvestTileHand's shipment tile. Throws an exception if this Hand does not contain a
	// shipment tile.
	HarvestTile* ship();
	// prints all the harvest tiles contained in the hand
	void display();

private:

	HarvestTile* one;
	HarvestTile* two;
	HarvestTile* shipment;

	bool isEmpty();
	bool isFull();

};

// The collection of Buildings owned by a Player.
class BuildingHand {
	
public:
	// Constructs a new BuildingHand object.
	BuildingHand();
	// Constructs a new BuildingHand object with the same contents as the specified BuildingHand.
	BuildingHand(const BuildingHand&);
	// Destroys this BuildingHand.
	~BuildingHand();
	// Adds the specified Building to this BuildingHand.
	void insert(Building*);
	// Returns the Building selected by a Player. Throws an exception if the specified selection
	// does not exist.
	Building* select(int);
	// prints all the buildings contained in the hand
	void display();

private:

	std::vector<Building*>* ownedBuildings;

	bool isEmpty();

};
