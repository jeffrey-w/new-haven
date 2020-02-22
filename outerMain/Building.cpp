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

BuildingToken* Building::next() {
	if (*spent) {
		throw new std::exception(); // TODO need richer exception type;
	}
}

void Building::display() const {
	// TODO
}
