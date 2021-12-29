#include <sstream>

#include "BuildingPool.h"

using std::string;
using std::vector;

BuildingPool::BuildingPool() {
    for (int i = 0; i < SIZE; i++) {
        buildings.push_back(nullptr);
    }
}

BuildingPool::BuildingPool(const BuildingPool& other) {
    for (auto& building : other.buildings) {
        buildings.push_back(building);
    }
}

BuildingPool::~BuildingPool() {
    for (auto& building : buildings) {
        delete building;
    }
}

size_t BuildingPool::getSize() const {
    return buildings.size();
}

void BuildingPool::replenish(Deck<Building*>* deck) {
    for (int i = 0; i < SIZE; i++) {
        if (deck->isEmpty()) {
            return;
        }
        if (!buildings[i]) {
            buildings[i] = deck->draw();
        }
    }
}

Building* BuildingPool::remove(int selection) {
    Building* result = nullptr;
    if (selection < 0 || selection > SIZE - 1) {
        throw std::out_of_range("Selection not in range.");
    }
    if (!(result = buildings[selection])) {
        throw std::invalid_argument("Building unavailable.");
    }
    buildings[selection] = nullptr;
    return result;
}

string BuildingPool::toString() const {
    std::ostringstream stream;
    Building::printBuildings(stream, buildings);
    stream << '\n';
    return stream.str();
}
