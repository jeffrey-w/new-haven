#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "../pieces/Building.h"
#include "../pieces/HarvestTile.h"
#include "../util/Random.h"

// A stack of pieces.
template<class T>
class Deck {

  public:
    // Constructs a new Deck object.
    Deck() = default;

    // Constructs a new Deck object with the same contents as the speciifed Deck.
    Deck(const Deck& other) : Deck() {
        for (auto piece : other.pieces) {
            pieces->push_back(T(piece));
        }
    }

    // Destroys this Deck.
    ~Deck() = default;

    // Returns true iff this Deck has no pieces in it.
    bool isEmpty() const {
        return pieces.empty();
    }

    // Returns the number of Pieces in this Deck.
    size_t getSize() const {
        return pieces.size();
    }

    // Puts the specified Piece on the top of this Deck.
    void add(T piece) {
        pieces.push_back(piece);
    }

    // Removes and returns the Piece at the top of this Deck. Throws an exception if this Deck is empty.
    T draw() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot draw from the empty deck.");
        }
        T piece = pieces.back();
        pieces.pop_back();
        return piece;
    }

    // Induces a random ordering on the Pieces in this Deck.
    void shuffle() {
        std::shuffle(pieces.begin(), pieces.end(), Random::generator);
    }

  private:
    std::vector<T> pieces;
};

// Partial specialization to handle pointer types.
template<class T>
class Deck<T*> {

  public:
    Deck() = default;

    Deck(const Deck& other) : Deck() {
        for (auto& piece : other.pieces) {
            pieces.push_back(new T(*piece));
        }
    }

    ~Deck() {
        for (auto& piece : pieces) {
            delete piece;
        }
    }

    bool isEmpty() const {
        return pieces.empty();
    }

    size_t getSize() const {
        return pieces.size();
    }

    void add(T* piece) {
        pieces.push_back(piece);
    }

    T* draw() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot draw from the empty deck.");
        }
        T* piece = pieces.back();
        pieces.pop_back();
        return piece;
    }

    void shuffle() {
        std::shuffle(pieces.begin(), pieces.end(), Random::generator);
    }

  private:
    std::vector<T*> pieces;
};

// Returns a shuffled Deck of 60 HarvestTiles.
Deck<HarvestTile*>* harvestTileDeck();
// Returns a shuffled Deck of 144 Buildings.
Deck<Building*>* buildingDeck();