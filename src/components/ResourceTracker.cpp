#include <sstream>

#include "../pieces/AbstractToken.h"
#include "ResourceTracker.h"

using std::map;
using std::string;

ResourceTracker::ResourceTracker() {
    for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
        count[i] = 0;
    }
}

ResourceTracker::ResourceTracker(const ResourceTracker& other) {
    count = map<int, int>(other.count);
}

int ResourceTracker::countOf(int type) const {
    return count.at(AbstractToken::validateType(type));
}

void ResourceTracker::use(int type, int cost) {
    if (count[AbstractToken::validateType(type)] < cost) {
        throw std::runtime_error("Not enough resoures.");
    }
    count[type] -= cost;
}

void ResourceTracker::save(int type, int amount) {
    if (count[AbstractToken::validateType(type)] < 0) {
        throw std::runtime_error("Cannot save negative resources.");
    }
    count[type] += amount;
}

void ResourceTracker::reset() {
    for (auto& entry : count) {
        entry.second = 0;
    }
}

string ResourceTracker::toString() const {
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
