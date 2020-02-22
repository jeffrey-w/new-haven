#include "GBMap.h"

using std::vector;
using std::pair;

GBMap::GBMap() : GBMap(DEFAULT_NUM_PLAYERS) {}

GBMap::GBMap(int numPlayers) {
	setNumPlayers(numPlayers); // TODO document exception
	graph = TokenGraph::gridOf(height(), width());
	prev = nullptr;
}

void GBMap::setNumPlayers(int numPlayers) {
	if (!(numPlayers == 2 || numPlayers == 3 || numPlayers == 4)) {
		throw new std::exception(); // TODO need richer exception type
	}
	this->numPlayers = new int(numPlayers);
}

GBMap::~GBMap() {
	delete numPlayers;
	delete graph;
	delete prev;
}

void GBMap::setSquare(HarvestTile* tile, pair<int, int> square) { // TODO check that square is empty
	for (auto coordinate : coordinatesOf(square)) { // TODO document exception
		graph->setTokenAt(tile->tokenize(), coordinate);
	}
	prev = new pair<int, int>(square); // TODO avoid side effects
}

void GBMap::calculateResources(GatherFacility* resources) {
	if (!prev) {
		throw new std::exception(); // TODO need richer exception type
	}
	for (auto& coordinate : coordinatesOf(*prev)) {
		int type = graph->tokenAt(coordinate)->getType();
		if (!resources->isCalculated(type)) {
			int amount = graph->search(coordinate); // TODO document exception
			resources->incrementBy(type, amount);
			resources->setCalculated(type);
		}
	}
}

int GBMap::height() {
	switch (*numPlayers) {
	case 2:
		return DIM_MIN;
	case 3:
	case 4:
		return DIM_MAX;
	}
}

int GBMap::width() {
	switch (*numPlayers) {
	case 2:
	case 3:
		return DIM_MIN;
	case 4:
		return DIM_MAX;
	}
}

vector<pair<int, int>> GBMap::coordinatesOf(pair<int, int> square) {
	validateSquare(square); // TODO document exception
	vector<pair<int, int>> coordinates(4); // TODO avoid magic constants
	pair<int, int> rowLimits = expand(square.first);
	pair<int, int> colLimits = expand(square.second);
	for (int i = rowLimits.first; i <= rowLimits.second; i++) {
		for (int j = colLimits.first; j <= colLimits.second; j++) {
			coordinates.push_back({ i, j });
		}
	}
	return coordinates;
}

std::pair<int, int> GBMap::expand(int index) {
	if (index == 0) {
		return { 0, 1 };
	}
	pair<int, int> prev = expand(index - 1);
	return { prev.first + 2, prev.second + 1 };
}

pair<int, int> GBMap::validateSquare(pair<int, int> square) {
	int row = square.first, col = square.second;
	switch (*numPlayers) {
	case 4:
		if (isOnCorner(row, col)) {
			throw new std::exception(); // TODO need richer exception type
		}
	case 2:
	case 3:
		if (row < 0 || row >= width() || col < 0 || col >= height()) {
			throw new std::exception(); // TODO need richer exception type
		}
	}
	return square;
}

bool GBMap::isOnCorner(int row, int col) {
	return (row == 0 || row == height() - 1) && (col == 0 || col == width() - 1);
}
