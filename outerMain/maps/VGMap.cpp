#include <iostream>
#include <queue>

#include "VGMap.h"

using std::array;
using std::map;
using std::pair;
using std::queue;
using std::cout;

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
}

void VGMap::validatePlacement(Building* building, pair<int, int> circle) {
    int row = circle.first, col = circle.second, type;
    // Null check.
    if (!building) {
        throw std::runtime_error("Cannot place the null building.");
    }
    // Bounds check.
    if(row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) {
        throw std::invalid_argument("Cirlce is not on board.");
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

bool VGMap::valuesMatch(Building* building, int row) {
    return building->getValue() == HEIGHT - row;
}

void VGMap::calculateScore(BuildFacility* score) {
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

void VGMap::display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            BuildingToken* building = static_cast<BuildingToken*>(graph->tokenAt({ i, j }));
            if (building) {
                building->display();
                cout << '\t';
            }
            else {
                cout << "-\t";
            }
        }
        cout << "\n\n";
    }
}
