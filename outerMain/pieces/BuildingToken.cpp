#include <iostream>
#include <string>

#include "../maps/VGMap.h"
#include "../util/Random.h"
#include "BuildingToken.h"

BuildingToken::BuildingToken() : BuildingToken(randomType(), randomValue()) {}

BuildingToken::BuildingType BuildingToken::randomType() {
	return static_cast<BuildingType>(Random::next(0, 3));
}

int BuildingToken::randomValue() {
	return Random::next(1, VGMap::HEIGHT);
}

BuildingToken::BuildingToken(BuildingType type, int value) {
	this->type = new BuildingType(type);
	this->value = new int(validateValue(value));
	this->faceUp = new bool(false);
}

int BuildingToken::validateValue(int value) {
	if (value < 1 || value > VGMap::HEIGHT) {
		throw std::invalid_argument("Value must be between 1 and "
			+ std::to_string(VGMap::HEIGHT) + ".");
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
	if (isPlaced()) {
		throw std::runtime_error("Cannot flip Building after placing it.");
	}
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
            std::cout << "F";
            break;
        case BuildingType::MEADOW:
            std::cout << "M";
            break;
        case BuildingType::QUARRY:
			std::cout << "Q";
            break;
        case BuildingType::WHEATFIELD:
            std::cout << "W";
            break;
    }
}
