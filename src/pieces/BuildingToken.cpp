#include <sstream>

#include "../maps/VGMap.h"
#include "../util/Random.h"
#include "BuildingToken.h"

BuildingToken::BuildingToken() : BuildingToken(randomType(), randomValue()) {
}

BuildingToken::BuildingType BuildingToken::randomType() {
    return static_cast<BuildingType>(Random::next(0, 3));
}

int BuildingToken::randomValue() {
    return Random::next(1, VGMap::HEIGHT);
}

BuildingToken::BuildingToken(BuildingType type, int value) {
    this->type = type;
    this->value = validateValue(value);
    this->faceUp = false;
}

int BuildingToken::validateValue(int value) {
    if (value < 1 || value > VGMap::HEIGHT) {
        throw std::invalid_argument("Value must be between 1 and " + std::to_string(VGMap::HEIGHT) + ".");
    }
    return value;
}

BuildingToken::BuildingToken(const BuildingToken& other) : AbstractToken(other) {
    type = other.type;
    value = other.value;
    faceUp = other.faceUp;
}

BuildingToken* BuildingToken::clone() const {
    return new BuildingToken(*this);
}

void BuildingToken::flip() {
    faceUp = !faceUp;
}

bool BuildingToken::isFaceUp() const {
    return faceUp;
}

int BuildingToken::getType() const {
    return static_cast<int>(type);
}

int BuildingToken::getValue() const {
    return value;
}

std::string BuildingToken::toString() const {
    std::ostringstream stream;
    switch (type) {
    case BuildingType::FOREST:
        stream << "F";
        break;
    case BuildingType::MEADOW:
        stream << "M";
        break;
    case BuildingType::QUARRY:
        stream << "Q";
        break;
    case BuildingType::WHEATFIELD:
        stream << "W";
        break;
    }
    return stream.str();
}
