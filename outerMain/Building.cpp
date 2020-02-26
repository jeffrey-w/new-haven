#include <stdexcept>

#include "Building.h"

Building::Building() {
	token = new BuildingToken(); // Default constructor returns a random BuildingToken.
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

bool Building::isSpent() const {
	return token->isPlaced();
}

BuildingToken* Building::tokenize() {
	if (isSpent()) {
		throw std::logic_error("This Building has already been used.");
	}
	return token;
}

