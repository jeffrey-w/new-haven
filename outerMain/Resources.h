#pragma once

#include <stack>

#include "Building.h"
#include "HarvestTile.h"
#include "Piece.h"

class Deck {

public:

	Piece* draw();
	bool empty();

protected:

	virtual Piece* drawAs() = 0;

private:

	std::stack<Piece*>* pieces;

};

class BuildingDeck : public Deck {

public:

	Building* drawAs();

};

class HarvestTileDeck : public Deck {

public:

	HarvestTile* drawAs();

};
