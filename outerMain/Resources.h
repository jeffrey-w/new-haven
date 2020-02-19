#pragma once

#include <stack>

#include "Piece.h"
#include "Player.h"

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
