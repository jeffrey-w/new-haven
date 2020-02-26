#include <stdexcept>

#include "Building.h"

Building::Building() {
	token = new BuildingToken(); // Default constructor returns a random BuildingToken.
}

Building::Building(const Building& other) {
	token = new BuildingToken(*other.token);
}

<<<<<<< HEAD
Building::Building(const Building& obj)
{
	colour = new Type(*obj.colour);
	number = new int(*obj.number);
	faceUp = new bool(*obj.faceUp);
=======
Building::~Building() {
	delete token;
>>>>>>> jeff-working
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

