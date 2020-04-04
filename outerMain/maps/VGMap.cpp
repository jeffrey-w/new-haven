#include <iostream>
#include <queue>

#include "../util/Debug.h"
#include "VGMap.h"

using std::array;
using std::map;
using std::pair;
using std::queue;

VGMap::VGMap() {
    graph = TokenGraph::gridOf(HEIGHT, WIDTH);
}

VGMap::VGMap(const VGMap& other) : VGMap() {
    for (auto& entry : other.graph->tokens()) {
        BuildingToken* orig = static_cast<BuildingToken*>(entry.second);
        BuildingToken* building = orig ? new BuildingToken(*orig) : nullptr;
        graph->setTokenAt(building, entry.first);
    }
}

VGMap::~VGMap() {
	delete graph;
}

void VGMap::setCircle(Building* building, pair<int, int> circle) {
    validatePlacement(building, circle);
    graph->setTokenAt(building->tokenize(), circle);
    delete building;
}

void VGMap::validatePlacement(const Building* building, pair<int, int> circle) {
    int row = circle.first, col = circle.second, type;
    // Null check.
    if (!building) {
        throw std::invalid_argument("Cannot place the null building.");
    }
    // Bounds check.
    if(row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) {
        throw std::out_of_range("Cirlce is not on board.");
    }
    // Occupancy check.
    if (graph->tokenAt(circle)) {
        throw std::invalid_argument("Circle is already occupied.");
    }
    type = building->getType();
    // Type check (if type is already on map).
    if(graph->hasType(type) && !graph->adjacentHolds(circle, type)) {
        throw std::runtime_error("Building must be placed adjacent to same type.");
    }
    // Value check (if face up).
    if(building->isFaceUp() && !valuesMatch(building, circle.first)) {
        throw std::runtime_error("Face up buildings must be placed in appropriate row.");
    }
}

bool VGMap::valuesMatch(const Building* building, int row) {
    return building->getValue() == HEIGHT - row;
}

void VGMap::calculateScore(BuildFacility* score) {
    if (!score) {
        throw std::invalid_argument("Cannot record score on the null build facility.");
    }
    score->incrementBy(countRows() + countCols());
}

int VGMap::countRows() {
    int row, col, multiplier, score = 0;
    BuildingToken* building;
    for (row = 0; row < HEIGHT; row++) {
        multiplier = 2;
        for (col = 0; col < WIDTH; col++) {
            building = static_cast<BuildingToken*>(graph->tokenAt({ row, col }));
            if (building) {
                if (!building->isFaceUp()) {
                    multiplier = 1;
                }
            }
            else {
                break;
            }
        }
        if (col == WIDTH) {
            score += (WIDTH - row) * multiplier;
        }
    }
    return score;
}

int VGMap::countCols() {
    int row, col, multiplier, score = 0;
    BuildingToken* building;
    for (col = 0; col < WIDTH; col++) {
        multiplier = 2;
        for (row = 0; row < HEIGHT; row++) {
            building = static_cast<BuildingToken*>(graph->tokenAt({ row, col }));
            if (building) {
                if (!building->isFaceUp()) {
                    multiplier = 1;
                }
            }
            else {
                break;
            }
        }
        if (row == HEIGHT) {
            /*
             * Column scores are as follow:
             * 0:5 | 1:4 | 2:3 | 3:4 | 4:5
             */
            score += (HEIGHT - col + (col > 2 ? 2 * (col - 2) : 0)) * multiplier;
        }
    }
    return score;
}

void VGMap::display() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const VGMap& map) {
    stream << '\t';
    for (int i = 0; i < VGMap::WIDTH; i++) {
        stream << i << '\t';
    }
    stream << "\n\n\n";
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        stream << i << '\t';
        for (int j = 0; j < VGMap::WIDTH; j++) {
            BuildingToken* building = static_cast<BuildingToken*>(map.graph->tokenAt({ i, j }));
            if (building) {
                building->display();
                stream << '\t';
            }
            else {
                stream << VGMap::HEIGHT - i << "\t";
            }
        }
        stream << "\n\n\n";
    }
    return stream;
}
