#include <stdexcept>

#include "../util/Debug.h"
#include "Building.h"

Building::Building() {
	// Default constructor returns a random BuildingToken.
	token = new BuildingToken();
}

Building::Building(BuildingType type, int value) {
	token = new BuildingToken(type, value);
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

BuildingToken* Building::tokenize() {
	BuildingToken* token = this->token;
	this->token = nullptr;
	return token;
}

void Building::flip() {
	token->flip();
}

void Building::display() const {
	token->display();
}

std::ostream& operator<<(std::ostream& stream, const Building& building) {
	return stream << *building.token;
}
