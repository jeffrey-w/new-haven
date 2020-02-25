#include "Building.h"

Building::Building() {
	token = new BuildingToken(); // Default constructor returns a random BuildingToken.
}

Building::Building(const Building& other) : AbstractPiece(other) {
	token = new BuildingToken(*other.token);
}

Building::~Building() {
	delete token;
}

BuildingToken::BuildingType Building::getType() const {
	return static_cast<BuildingToken::BuildingType>(token->getType());
}

int Building::getValue() const {
	return token->getValue();
}

BuildingToken* Building::tokenize() {
/*	if (isSpent()) {//TODO uncomment, needed for testing though
		throw new std::exception(); // TODO need richer exception type;
	}*/
	spend();
	return token;
}

