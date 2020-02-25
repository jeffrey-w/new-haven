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

BuildingToken::BuildingType Building::getType() const {
	return static_cast<BuildingToken::BuildingType>(token->getType());
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
	//if (isSpent()) {//TODO uncomment, needed for testing though
	//	throw std::exception(); // TODO need richer exception type;
	//}
	return token;
}

