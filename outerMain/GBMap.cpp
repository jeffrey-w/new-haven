#include <iostream>

#include "GBMap.h"

using std::vector;
using std::pair;

GBMap::GBMap() : GBMap(DEFAULT_NUM_PLAYERS) {}

GBMap::GBMap(int numPlayers) {
	setNumPlayers(numPlayers);
	graph = TokenGraph::gridOf(height(), width());
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
}

void GBMap::setSquare(HarvestTile* tile, pair<int, int> square) { // TODO need to backtrack if tile is partially placed before call
	for (auto& coordinate : coordinatesOf(square, true)) {
		graph->setTokenAt(tile->tokenize(), coordinate);
	}
}

void GBMap::calculateResources(pair<int, int> from, GatherFacility* resources) {
	for (auto& coordinate : coordinatesOf(from)) {
		if (!graph->isBlack(coordinate)) { // coordinate has previously been reached by another search.
			int amount = graph->search(coordinate);
			int type = graph->tokenAt(coordinate)->getType();
			resources->incrementBy(type, amount);
		}
	}
}

void GBMap::display() {
	for (int i = 0; i < height(); i++) {
		for (int j = 0; j < width(); j++) {
			ResourceToken* resource = static_cast<ResourceToken*>(graph->tokenAt({ i, j }));
			if (resource) {
				resource->display();
				std::cout << '\t';
			}
			else {
				std::cout << "-\t";
			}
		}
		std::cout << "\n\n";
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

vector<pair<int, int>> GBMap::coordinatesOf(pair<int, int> square, bool ensureEmpty) {
	validateSquare(square);
	vector<pair<int, int>> coordinates;
	pair<int, int> rowLimits = expand(square.first);
	pair<int, int> colLimits = expand(square.second);
	for (int i = rowLimits.first; i <= rowLimits.second; i++) {
		for (int j = colLimits.first; j <= colLimits.second; j++) {
			coordinates.push_back({ i, j });
		}
	}
	if (ensureEmpty) {
		for (auto& coordinate : coordinates) {
			if (graph->tokenAt(coordinate)) {
				throw new std::exception(); // TODO need richer exception type
			}
		}
	}
	return coordinates;
}

void GBMap::validateSquare(pair<int, int> square) {
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
}

std::pair<int, int> GBMap::expand(int index) {
	if (index == 0) {
		return { 0, 1 };
	}
	pair<int, int> prev = expand(index - 1);
	return { prev.first + 2, prev.second + 2 };
}


bool GBMap::isOnCorner(int row, int col) {
	return (row == 0 || row == height() - 1) && (col == 0 || col == width() - 1);
}
