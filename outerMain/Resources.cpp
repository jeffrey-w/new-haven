#include <stdexcept>

#include "Resources.h"

using std::stack;
using std::vector;

Deck::Deck() {
	pieces = new stack<AbstractPiece*>();
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
	pieces->push(piece);
}

AbstractPiece* Deck::pop() {
	if (empty) {
		throw std::runtime_error("Cannot draw from an empty deck.");
	}
	AbstractPiece* result = pieces->top();
	pieces->pop();
	return result;
}

std::vector<AbstractPiece*>& Deck::asList() const {
	stack<AbstractPiece*> s;
	auto list = new vector<AbstractPiece*>();
	while (!pieces->empty()) {
		s.push(pieces->top());
		list->push_back(pieces->top());
		pieces->pop();
	}
	while (!s.empty()) {
		pieces->push(s.top());
		s.pop();
	}
	return *list;
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
