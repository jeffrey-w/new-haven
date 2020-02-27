#include <stdexcept>

#include "Building.h"

Building::Building() {
	// Default constructor returns a random BuildingToken.
	token = new BuildingToken();
}

Building::Building(const Building& other) {
	token = new BuildingToken(*other.token);
}

Building::~Building() {
	delete token;
}

int Building::getType() const {
	return token->getType();
}

bool Building::isFaceUp() const {
    return token->isFaceUp();
}

int Building::getValue() const {
	return token->getValue();
}

bool Building::isTokenized() const {
	return token->isPlaced();
}

BuildingToken* Building::tokenize() {
	if (isTokenized()) {
		throw std::logic_error("This Building has already been used.");
	}
	return token;
}

