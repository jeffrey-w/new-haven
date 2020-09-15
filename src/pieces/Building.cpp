#include <stdexcept>

#include "Building.h"

using std::vector;

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

void Building::printBuildings(std::ostream& stream, const vector<Building*>& buildings) {
    int number = 1;
    for (auto& building : buildings) {
        if (building) {
            stream << "╔═╤══════╗\t";
        }
    }
    stream << '\n';
    for (auto& building : buildings) {
        if (building) {
            stream << "║";
            stream << building->getValue();
            stream << "│      ║\t";
        }
    }
    stream << '\n';
    for (auto& building : buildings) {
        if (building) {
            stream << "╟─┘  ";
            stream << *building->token;
            stream << "   ║\t";
        }
    }
    stream << '\n';
    for (auto& building : buildings) {
        if (building) {
            stream << "║        ║\t";
        }
    }
    stream << '\n';
    for (auto& building : buildings) {
        if (building) {
            stream << "╚═══════[";
            stream << number;
            stream << "]\t";
        }
        number++;
    }
    stream << '\n';
}
