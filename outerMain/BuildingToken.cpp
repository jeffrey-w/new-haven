#include "BuildingToken.h"
#include "Random.h"
#include <iostream>
using std::cout;

BuildingToken::BuildingToken() : BuildingToken(randomType(), randomValue()) {}

BuildingToken::BuildingType BuildingToken::randomType() {
	return AS_TYPE(Random::next(0, 3), BuildingType);
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
		throw std::exception(); // TODO need richer exception type
	}
	return value;
}


BuildingToken::BuildingToken(const BuildingToken& other) : AbstractToken(other) {
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

bool BuildingToken::isFaceUp() const {
    return *faceUp;
}

int BuildingToken::getType() const {
	return static_cast<int>(*type);
}

int BuildingToken::getValue() const {
    return *value;
}

void BuildingToken::display() const {
    switch (*type) {
        case BuildingType::FOREST:
            cout << "F";
            break;
        case BuildingType::MEADOW:
            cout << "M";
            break;
        case BuildingType::QUARRY:
            cout << "Q";
            break;
        case BuildingType::WHEATFIELD:
            cout << "W";
            break;
    }
}
