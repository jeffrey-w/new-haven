#pragma once

#include <exception>

#include "AbstractPiece.h"
#include "BuildingToken.h"

class Building : public AbstractPiece {

public:

	Building();
	Building(Building&);
	~Building();
	BuildingToken* next();
	void display() const;

private:

	BuildingToken* token;

};

