#include "Building.h"

Building::Building() {
	token = new BuildingToken(); // Default constructor returns a random BuildingToken.
}

Building::Building(Building& other) {
	token = new BuildingToken(*other.token);
}

Building::~Building() {
	delete token;
}

BuildingToken* Building::tokenize() {
/*	if (isSpent()) {//TODO uncomment, needed for testing though
		throw new std::exception(); // TODO need richer exception type;
	}*/
	spend();
	return token;
}

