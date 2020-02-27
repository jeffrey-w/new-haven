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
    typePlaced = new array<bool,4>();
}

VGMap::VGMap(const VGMap& other) : VGMap() {
    for (auto& entry : other.graph->tokens()) {
        BuildingToken* orig = static_cast<BuildingToken*>(entry.second);
        BuildingToken* building = orig ? new BuildingToken(*orig) : nullptr;
        graph->setTokenAt(building, entry.first);
    }
    for (int i = 0; i < 4; i++) {
        (*typePlaced)[i] = (*other.typePlaced)[i];
    }
}

VGMap::~VGMap() {
	delete graph;
	delete typePlaced;
}

void VGMap::setCircle(Building* building, pair<int, int> circle) {
    validateCircle(circle);
    int type = building->getType();
    if(graph->hasType(type) && !graph->adjacentHolds(circle, type)) {
        throw std::logic_error("Building must be placed adjacent to same type.");
    }
    if(building->isFaceUp() && !valuesMatch(building, circle.first)) {
        throw std::logic_error("Face up buildings must be placed in appropriate row.");
    }
	graph->setTokenAt(building->tokenize(), circle);
    (*typePlaced)[type] = true;
}

void VGMap::validateCircle(pair<int, int> circle) {
    int row = circle.first, col = circle.second;
	if(row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) {
	    throw std::invalid_argument("Cirlce is not on board.");
	}
}

bool VGMap::valuesMatch(Building* building, int row) {
    return building->getValue() == HEIGHT - row;
}

void VGMap::calculateScore(VillageBuildingScoringFacility* score) {
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
