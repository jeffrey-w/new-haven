#include <sstream>
#include <string>

#include "../maps/VGMap.h"
#include "../pieces/AbstractToken.h"
#include "ScoringFacilities.h"

using std::map;
using std::string;

GatherFacility::GatherFacility() {
    for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
        count[i] = 0;
    }
}

GatherFacility::GatherFacility(const GatherFacility& other) {
    count = map<int, int>(other.count);
}

int GatherFacility::countOf(int type) const {
    return count.at(AbstractToken::validateType(type));
}

void GatherFacility::incrementBy(int type, int amount) {
    count[AbstractToken::validateType(type)] += amount;
}

void GatherFacility::reset() {
    for (auto& entry : count) {
        entry.second = 0;
    }
}

string GatherFacility::toString() const {
    std::ostringstream stream;
    stream << "┌───────────┬───────────┬───────────┬───────────┐\n";
    stream << "│ Sheep: M  │ Stone: Q  │ Timber: F │ Wheat: W  │\n";
    stream << "├───────────┼───────────┼───────────┼───────────┤\n";
    for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
        stream << "│         ";
        stream << count.at(i);
        stream << " ";
    }
    stream << "│\n";
    stream << "└───────────┴───────────┴───────────┴───────────┘\n";
    return stream.str();
}

BuildFacility::BuildFacility() : villagers(0), built(0), unbuilt(0) {
}

BuildFacility::BuildFacility(const BuildFacility& other) : BuildFacility() {
    setVillagers(other.villagers);
    setBuilt(other.built);
    setUnbuilt(other.unbuilt);
}

int BuildFacility::getVillagers() const {
    return villagers;
}

int BuildFacility::getBuilt() const {
    return built;
}

int BuildFacility::getUnbuilt() const {
    return unbuilt;
}

void BuildFacility::setVillagers(int villagers) {
    this->villagers = validateScore(villagers);
}

void BuildFacility::setBuilt(int built) {
    this->built = validateScore(built);
}

void BuildFacility::setUnbuilt(int unbuilt) {
    this->unbuilt = validateScore(unbuilt);
}

int BuildFacility::validateScore(int score) {
    if (score < 0) {
        throw std::invalid_argument("Score must be nonnegative.");
    }
    return score;
}

bool BuildFacility::operator<(const BuildFacility& other) const {
    if (villagers != other.villagers) {
        return villagers < other.villagers;
    }
    if (built != other.built) {
        return built < other.built;
    }
    return other.unbuilt < unbuilt;
}

bool BuildFacility::operator==(const BuildFacility& other) const {
    return villagers == other.villagers && built == other.built && unbuilt == other.unbuilt;
}
