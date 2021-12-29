#include <sstream>

#include "BuildingHand.h"

using std::string;

BuildingHand::BuildingHand(const BuildingHand& other) {
    for (auto& building : other.buildings) {
        buildings.push_back(new Building(*building));
    }
}

BuildingHand::~BuildingHand() {
    for (auto& building : buildings) {
        delete building;
    }
}

size_t BuildingHand::getSize() const {
    return buildings.size();
}

void BuildingHand::insert(Building* building) {
    buildings.push_back(building);
    notify();
}

Building* BuildingHand::select(int selection) {
    int index = validateSelection(selection);
    Building* building = buildings[index];
    buildings.erase(buildings.begin() + index);
    return building;
}

int BuildingHand::typeOf(int selection) const {
    return buildings[validateSelection(selection)]->getType();
}

int BuildingHand::validateSelection(int selection) const {
    if (selection < 0 || selection > getSize() - 1) {
        throw std::out_of_range("Selection not in range.");
    }
    return selection;
}

string BuildingHand::toString() const {
    std::ostringstream stream;
    Building::printBuildings(stream, buildings);
    stream << '\n';
    return stream.str();
}