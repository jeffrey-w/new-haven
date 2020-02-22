#pragma once

#include "AbstractPiece.h"
#include "BuildingToken.h"

class Building : public AbstractPiece {

public:

	Building();
	Building(Building&);
	~Building();
	BuildingToken* next();

private:

	BuildingToken* token;

};

