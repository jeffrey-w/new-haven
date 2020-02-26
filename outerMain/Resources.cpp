#include "Resources.h"

AbstractPiece* Deck::draw() {
	if (empty()) {
		throw std::exception(); // TODO need richer exception type
	}
	AbstractPiece* piece = pieces->top();
	pieces->pop();
	return piece;
}

bool Deck::empty() {
	return pieces->empty();
}

void Deck::insert(AbstractPiece* piece) {
	pieces->push(piece);
}

void BuildingDeck::add(Building* building) {
	insert(building);
}

Building* BuildingDeck::drawAs() {
	return static_cast<Building*>(draw());
}

void HarvestTileDeck::add(HarvestTile* tile) {
	insert(tile);
}

HarvestTile* HarvestTileDeck::drawAs() {
	return static_cast<HarvestTile*>(draw());
}
