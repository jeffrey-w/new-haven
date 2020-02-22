#include "BuildingToken.h"
#include "Random.h"

BuildingToken::BuildingToken() : BuildingToken(randomType(), randomValue()) {}

BuildingToken::BuildingType BuildingToken::randomType() {
	return static_cast<BuildingType>(Random::next(0, 3)); // TODO can bound be obtained programmatically?
}

int BuildingToken::randomValue() {
	return Random::next(1, 6); // TODO avoid magic constants
}

BuildingToken::BuildingToken(BuildingType type, int value) {
	this->type = new BuildingType(type);
	this->value = new int(validateValue(value));
	this->faceUp = new bool(false);
}

int BuildingToken::validateValue(int value) {
	if (value < 1 || value > 6) { // TODO avoid magic constatns
		throw new std::exception(); // TODO need richer exception type
	}
	return value;
}


BuildingToken::BuildingToken(BuildingToken& other) {
	type = new BuildingType(*other.type);
	value = new int(*other.value);
	faceUp = new bool(*other.faceUp);
}

BuildingToken::~BuildingToken()
{
	delete type;
	delete value;
	delete faceUp;
}

void BuildingToken::flip() {
	*faceUp = !(*faceUp);
}

bool BuildingToken::getFaceUp() const {
    return *faceUp;
}

int BuildingToken::getType() const {
	return static_cast<int>(*type);
}

int BuildingToken::getValue() const {
    return *value;
}

void BuildingToken::display() const {
	// TODO
}
