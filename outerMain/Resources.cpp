#include "Resources.h"

AbstractPiece* Deck::draw() {
	if (empty()) {
		throw new std::exception(); // TODO need richer return type
	}
	AbstractPiece* piece = pieces->top();
	pieces->pop();
	return piece;
}

bool Deck::empty() {
	return pieces->empty();
}

Building* BuildingDeck::drawAs() {
	return static_cast<Building*>(draw());
}

HarvestTile* HarvestTileDeck::drawAs() {
	return static_cast<HarvestTile*>(draw());
}
