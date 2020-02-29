#include <stdexcept>

#include "Resources.h"

using std::vector;

Deck::Deck() {
	pieces = new vector<AbstractPiece*>();
}

Deck::~Deck() {
	delete pieces;
}

bool Deck::empty() const {
	return pieces->empty();
}

void Deck::push(AbstractPiece* piece) {
	if (!piece) {
		throw std::invalid_argument("Cannot add the null Piece to a deck.");
	}
	pieces->push_back(piece);
}

AbstractPiece* Deck::pop() {
	if (empty()) {
		throw std::runtime_error("Cannot draw from an empty deck.");
	}
	AbstractPiece* result = pieces->back();
	pieces->pop_back();
	return result;
}

std::vector<AbstractPiece*>& Deck::asList() const {
	return *pieces;
}

BuildingDeck::BuildingDeck() : Deck() {}

BuildingDeck::BuildingDeck(const BuildingDeck& other) : BuildingDeck() {
	for (auto& piece : other.asList()) {
		Building* building = static_cast<Building*>(piece);
		push(new Building(*building));
	}
}

void BuildingDeck::add(Building* building) {
	push(building);
}

Building* BuildingDeck::draw() {
	return static_cast<Building*>(pop());
}

HarvestTileDeck::HarvestTileDeck() : Deck() {}

HarvestTileDeck::HarvestTileDeck(const HarvestTileDeck& other) : HarvestTileDeck() {
	for (auto piece : other.asList()) {
		HarvestTile* tile = static_cast<HarvestTile*>(piece);
		push(new HarvestTile(*tile));
	}
}

void HarvestTileDeck::add(HarvestTile* tile) {
	push(tile);
}

HarvestTile* HarvestTileDeck::draw() {
	return static_cast<HarvestTile*>(pop());
}
