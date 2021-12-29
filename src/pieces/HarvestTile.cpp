#include "../util/Random.h"
#include "HarvestTile.h"

using std::vector;

HarvestTile::HarvestTile() {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        // Default constructor returns a random ResourceToken.
        resources.push_back(new ResourceToken());
    }
}

HarvestTile::HarvestTile(ResourceToken* one, ResourceToken* two, ResourceToken* three, ResourceToken* four) {
    // Internal represntation: {one, two, four, three}.
    resources.push_back(one);
    resources.push_back(two);
    resources.push_back(four);
    resources.push_back(three);
}

HarvestTile::HarvestTile(const HarvestTile& other) {
    for (auto& resource : other.resources) {
        resources.push_back(new ResourceToken(*resource));
    }
    orientation = other.orientation;
}

HarvestTile::~HarvestTile() {
    for (auto& resource : resources) {
        delete resource;
    }
}

void HarvestTile::rotate() {
    orientation.reorient();
}

ResourceToken* HarvestTile::tokenize() {
    int index = orientation.current();
    ResourceToken* token = resources[index];
    resources[index] = nullptr;
    return token;
}

void HarvestTile::printTiles(std::ostream& stream, const vector<HarvestTile*> tiles) {
    int number = 1;
    bool isRegular;
    for (auto& tile : tiles) {
        if (tile) {
            stream << "╔════════╤════════╗\t";
        }
    }
    stream << '\n';
    for (auto& tile : tiles) {
        if (tile) {
            stream << "║        │        ║\t";
        }
    }
    stream << '\n';
    for (auto& tile : tiles) {
        isRegular = number++ < NUM_RESOURCES - 1;
        if (tile) {
            stream << "║   ";
            if (isRegular) {
                stream << *tile->resources[tile->orientation.origin & NUM_RESOURCES - 1];
            } else {
                stream << "--";
            }
            stream << "   │   ";
            if (isRegular) {
                stream << *tile->resources[tile->orientation.origin + Orientation::UPPER_RIGHT & NUM_RESOURCES - 1];
            } else {
                stream << "--";
            }
            stream << "   ║\t";
        }
    }
    number = 1;
    stream << '\n';
    for (auto& tile : tiles) {
        stream << "║        │        ║\t";
    }
    stream << '\n';
    for (auto& tile : tiles) {
        stream << "╟────────┼────────╢\t";
    }
    stream << '\n';
    for (auto& tile : tiles) {
        stream << "║        │        ║\t";
    }
    stream << '\n';
    for (auto& tile : tiles) {
        isRegular = number++ < NUM_RESOURCES - 1;
        if (tile) {
            stream << "║   ";
            if (isRegular) {
                stream << *tile->resources[tile->orientation.origin + Orientation::LOWER_RIGHT & NUM_RESOURCES - 1];
            } else {
                stream << "--";
            }
            stream << "   │   ";
            if (isRegular) {
                stream << *tile->resources[tile->orientation.origin + Orientation::LOWER_LEFT & NUM_RESOURCES - 1];
            } else {
                stream << "--";
            }
            stream << "   ║\t";
        }
    }
    number = 1;
    stream << '\n';
    for (auto& tile : tiles) {
        if (tile) {
            stream << "║        │        ║\t";
        }
    }
    stream << '\n';
    for (auto& tile : tiles) {
        if (tile) {
            stream << "╚════════╧═══════[";
            stream << number;
            stream << "]\t";
        }
        number++;
    }
    stream << '\n';
}

HarvestTile::Orientation::Orientation() {
    origin = Random::next(0, NUM_RESOURCES - 1);
    pos = 0;
}

void HarvestTile::Orientation::reorient() {
    if (pos) {
        throw std::runtime_error("This tile is already being tokenized.");
    }
    origin++;
}

int HarvestTile::Orientation::current() {
    int current = pos++;
    switch (current) {
    case UPPER_LEFT:
        current = origin;
        break;
    case UPPER_RIGHT:
        current = origin + UPPER_RIGHT;
        break;
    case LOWER_LEFT:
        current = origin + LOWER_RIGHT;
        break;
    case LOWER_RIGHT:
        current = origin + LOWER_LEFT;
        break;
    default:
        throw std::length_error("This tile has already been tokenized.");
    }
    return current & NUM_RESOURCES - 1;
}
