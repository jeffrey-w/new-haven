#include <sstream>

#include "VGMap.h"

using std::map;
using std::pair;
using std::string;

VGMap::VGMap() {
    graph = TokenGraph::gridOf(HEIGHT, WIDTH);
}

VGMap::VGMap(const VGMap& other) : VGMap() {
    for (auto& entry : other.graph->tokens()) {
        AbstractToken* token = entry.second;
        graph->setTokenAt(token ? token->clone() : nullptr, entry.first);
    }
}

VGMap::~VGMap() {
    delete graph;
}

bool VGMap::emptyAt(pair<int, int> circle) const {
    return graph->emptyAt(circle);
}

int VGMap::buildingCount() const {
    return HEIGHT * WIDTH - graph->emptyNodes();
}

bool VGMap::hasType(int type) const {
    return graph->hasType(type);
}

bool VGMap::adjacentHolds(pair<int, int> circle, int type) const {
    return graph->adjacentHolds(circle, type);
}

void VGMap::setCircle(Building* building, pair<int, int> circle) {
    validatePlacement(building, circle);
    graph->setTokenAt(building->tokenize(), circle);
    notify();
    delete building;
}

void VGMap::validatePlacement(const Building* building, pair<int, int> circle) {
    int row = circle.first, col = circle.second, type;
    // Null check.
    if (!building) {
        throw std::invalid_argument("Cannot place the null building.");
    }
    // Bounds check.
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) {
        throw std::out_of_range("Cirlce is not on board.");
    }
    // Occupancy check.
    if (graph->tokenAt(circle)) {
        throw std::invalid_argument("Circle is already occupied.");
    }
    // Type check (if type is already on map).
    if (hasType(building->getType()) && !graph->adjacentHolds(circle, building->getType())) {
        throw std::runtime_error("Building must be placed adjacent to same type.");
    }
    // Value check (if face up).
    if (building->isFaceUp() && !valuesMatch(building, circle.first)) {
        throw std::runtime_error("Face up buildings must be placed in appropriate row.");
    }
}

bool VGMap::valuesMatch(const Building* building, int row) {
    return building->getValue() == HEIGHT - row;
}

int VGMap::calculateScore() {
    return countRows() + countCols();
}

int VGMap::countRows() {
    int row, col, multiplier, score = 0;
    BuildingToken* building;
    for (row = 0; row < HEIGHT; row++) {
        multiplier = 1;
        for (col = 0; col < WIDTH; col++) {
            building = static_cast<BuildingToken*>(graph->tokenAt({row, col}));
            if (building) {
                if (!building->isFaceUp()) {
                    multiplier = 0;
                }
            } else {
                break;
            }
        }
        if (col == WIDTH) {
            score += (HEIGHT - row) << multiplier;
        }
    }
    return score;
}

int VGMap::countCols() {
    int row, col, multiplier, score = 0;
    BuildingToken* building;
    for (col = 0; col < WIDTH; col++) {
        multiplier = 1;
        for (row = 0; row < HEIGHT; row++) {
            building = static_cast<BuildingToken*>(graph->tokenAt({row, col}));
            if (building) {
                if (!building->isFaceUp()) {
                    multiplier = 0;
                }
            } else {
                break;
            }
        }
        if (row == HEIGHT) {
            /*
             * Column scores are as follow:
             * 0:5 | 1:4 | 2:3 | 3:4 | 4:5
             */
            score += (HEIGHT - col + (col > 2 ? (col - 2) << 1 : 0)) << multiplier;
        }
    }
    return score;
}

string VGMap::toString() const {
    std::ostringstream stream;
    stream << "    1    2    3    4    5";
    stream << '\n';
    stream << "  ┏━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    for (int i = 0; i < HEIGHT; i++) {
        stream << (char)('A' + i);
        stream << " ┃ ";
        for (int j = 0; j < WIDTH; j++) {
            AbstractToken* token = graph->tokenAt({i, j});
            if (token) {
                stream << *token;
            } else {
                stream << HEIGHT - i;
            }
            if (j < WIDTH - 1) {
                stream << "    ";
            }
        }
        stream << " ┃\n";
        if (i < HEIGHT - 1) {
            stream << "  ┃                       ┃\n";
        }
    }
    stream << "  ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    return stream.str();
}
