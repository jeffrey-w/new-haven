#include <queue>
#include <sstream>

#include "../util/Debug.h"
#include "VGMap.h"

using std::array;
using std::map;
using std::pair;
using std::queue;
using std::string;

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

bool VGMap::emptyAt(pair<int, int> circle) {
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
	delete building;
	notify();
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

int VGMap::calculateScore() {
	return countRows() + countCols();
}

int VGMap::countRows() {
	int row, col, multiplier, score = 0;
	BuildingToken* building;
	for (row = 0; row < HEIGHT; row++) {
		multiplier = 1;
		for (col = 0; col < WIDTH; col++) {
			building = static_cast<BuildingToken*>(graph->tokenAt({ row, col }));
			if (building) {
				if (!building->isFaceUp()) {
					multiplier = 0;
				}
			}
			else {
				break;
			}
		}
		if (col == WIDTH) {
			score += (WIDTH - row) << multiplier;
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
			building = static_cast<BuildingToken*>(graph->tokenAt({ row, col }));
			if (building) {
				if (!building->isFaceUp()) {
					multiplier = 0;
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
			score += (HEIGHT - col + (col > 2 ? 2 * (col - 2) : 0)) << multiplier;
		}
	}
	return score;
}

string* VGMap::toString() const {
	std::ostringstream stream;
	stream << '\t';
	for (int i = 0; i < WIDTH; i++) {
		stream << i << '\t';
	}
	stream << "\n\n\n";
	for (int i = 0; i < HEIGHT; i++) {
		stream << i << '\t';
		for (int j = 0; j < WIDTH; j++) {
			BuildingToken* building = static_cast<BuildingToken*>(graph->tokenAt({ i, j }));
			if (building) {
				stream << *building << '\t';
			}
			else {
				stream << HEIGHT - i << "\t";
			}
		}
		stream << "\n\n\n";
	}
	return new string(stream.str());
}
