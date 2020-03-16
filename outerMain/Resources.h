#pragma once

#include <stdexcept>
#include <type_traits>
#include <vector>

#include "pieces/AbstractPiece.h"
#include "pieces/Building.h"
#include "pieces/HarvestTile.h"

// A stack of pieces.
template <class T>
class Deck {

public:

	// Constructs a new Deck object.
	Deck() {
		pieces = new std::vector<T>();
	}

	// Constructs a new Deck object with the same contents as the speciifed Deck.
	Deck(const Deck& other) : Deck() {
		for (auto piece : *other.pieces) {
			pieces->push_back(piece);
		}
	}

	// Destroys this Deck.
	~Deck() {
		delete pieces;
	}

	// Returns true iff this Deck has no pieces in it.
	bool isEmpty() const {
		return pieces->empty();
	}

	// Returns the number of Pieces in this Deck.
	size_t getSize() const {
		return pieces->size();
	}

	// Puts the specified Piece on the top of this Deck.
	void add(T piece) {
		pieces->push_back(piece);
	}

	// Removes and returns the Piece at the top of this Deck. Throws an exception if this Deck is
	// empty.
	T draw() {
		if (isEmpty()) {
			throw std::runtime_error("Cannot draw from the empty deck.");
		}
		T piece = pieces->back();
		pieces->pop_back();
		return piece;
	}
	
private:

	std::vector<T>* pieces;

};

// Partial specialization to handle pointer types.
template <class T>
class Deck<T*> {

public:

	Deck() {
		pieces = new std::vector<T*>();
	}

	Deck(const Deck& other) : Deck() {
		for (auto& piece : *other.pieces) {
			pieces->push_back(new T(*piece));
		}
	}
	
	~Deck() {
		delete pieces;
	}
	
	bool isEmpty() const {
		return pieces->empty();
	}
	
	size_t getSize() const {
		return pieces->size();
	}

	void add(T* piece) {
		pieces->push_back(piece);
	}
	
	T* draw() {
		if (isEmpty()) {
			throw std::runtime_error("Cannot draw from the empty deck.");
		}
		T* piece = pieces->back();
		pieces->pop_back();
		return piece;
	}

private:

	std::vector<T*>* pieces;

};

// Returns a Deck of 60 HarvestTiles.
Deck<HarvestTile*>* harvestTileDeck();
// Returns a Deck of 144 Buildings.
Deck<Building*>* buildingDeck();

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
	// Returns this HarvestTileHand's shipment tile. Throws an exception if this Hand does not contain a
	// shipment tile.
	HarvestTile* ship();
	// Writes this HarvestTileHand to the standard outoput stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const HarvestTileHand&);

private:

	HarvestTile* one;
	HarvestTile* two;
	HarvestTile* shipment;

	bool isEmpty() const;
	bool isFull() const;

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
	// Gives the aggregate value of all of the Buildings in this BuildingHand.
	int worth();
	// Writes this BuildingHand to the standard outoput stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const BuildingHand&);

private:

	std::vector<Building*>* owned;

	bool isEmpty() const;

};
