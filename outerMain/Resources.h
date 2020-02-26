#pragma once

#include <stack>

#include "AbstractPiece.h"
#include "Building.h"
#include "HarvestTile.h"

class Deck {

public:

	AbstractPiece* draw();
	bool empty();

protected:

	void insert(AbstractPiece*);
	virtual AbstractPiece* drawAs() = 0;

private:

	std::stack<AbstractPiece*>* pieces;

};

class BuildingDeck : public Deck {

public:

	void add(Building*);
	Building* drawAs();

};

class HarvestTileDeck : public Deck {

public:

	void add(HarvestTile*);
	HarvestTile* drawAs();

};
