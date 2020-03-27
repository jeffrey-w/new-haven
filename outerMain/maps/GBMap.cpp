#include <iostream>

#include "../Game.h"
#include "../util/Debug.h"
#include "GBMap.h"

using std::pair;
using std::vector;

GBMap::GBMap() : GBMap(Game::DEFAULT_NUM_PLAYERS) {}

GBMap::GBMap(int numPlayers) {
	setNumPlayers(numPlayers);
	graph = TokenGraph::gridOf(height(), width());
}

void GBMap::setNumPlayers(int numPlayers) {
	if (!(numPlayers == 2 || numPlayers == 3 || numPlayers == 4)) {
		throw std::invalid_argument("Number of players must be between 2 and 4.");
	}
	this->numPlayers = new int(numPlayers);
}

GBMap::GBMap(const GBMap& other) : GBMap(*other.numPlayers) {
	for (auto& entry : other.graph->tokens()) {
		ResourceToken* orig = static_cast<ResourceToken*>(entry.second);
		ResourceToken* resource = orig ? new ResourceToken(*orig) : nullptr;
		graph->setTokenAt(resource, entry.first);
	}
}

GBMap::~GBMap() {
	delete numPlayers;
	delete graph;
}

int GBMap::getNumPlayers() const {
	return *numPlayers;
}

void GBMap::setSquare(HarvestTile* tile, pair<int, int> square) {
	if (!tile) {
		throw std::invalid_argument("Cannot place the null tile.");
	}
	for (auto& coordinate : coordinatesOf(square, true)) {
		graph->setTokenAt(tile->tokenize(), coordinate);
	}
	delete tile;
	tile = nullptr;
}

void GBMap::calculateResources(pair<int, int> from, GatherFacility* resources,
		ResourceToken* shipment) {
	// Place shipment tile if it has been played.
	if (shipment) {
		for (auto& coordinate : coordinatesOf(from)) {
			graph->setTokenAt(new ResourceToken(*shipment), coordinate);
		}
	}
	// Perform search for conntected resources starting from the four coordinates in from
	for (auto& coordinate : coordinatesOf(from)) {
		// Coordinate is occupied and has not been reached by a previous search.
		if (graph->tokenAt(coordinate) && !graph->isSearched(coordinate)) {
			int type = graph->tokenAt(coordinate)->getType();
			// Only search if it's possible to locate like resources.
			int amount = graph->hasType(type) ? graph->search(coordinate) : 1;
			resources->incrementBy(type, amount);
		}
	}
	// Remove shipment tile.
	if (shipment) {
		for (auto& coordinate : coordinatesOf(from)) {
			graph->removeTokenAt(coordinate);
		}
	}
	// Clean up graph for next search.
	graph->cleanupSearch();
}

void GBMap::display() const {
	std::cout << *this;
}

int GBMap::height() const {
	switch (*numPlayers) {
	case 2:
		return DIM_MIN;
	case 3:
	case 4:
		return DIM_MAX;
	default:
		throw std::logic_error("FATAL ERROR: numPlayers has unexpected value.");
	}
}

int GBMap::width() const {
	switch (*numPlayers) {
	case 2:
	case 3:
		return DIM_MIN;
	case 4:
		return DIM_MAX;
	default:
		throw std::logic_error("FATAL ERROR: numPlayers has unexpected value.");
	}
}

vector<pair<int, int>> GBMap::coordinatesOf(pair<int, int> square, bool ensureEmpty) {
	validateSquare(square);
	vector<pair<int, int>> coordinates = expand(square);
	if (ensureEmpty) {
		for (auto& coordinate : coordinates) {
			if (graph->tokenAt(coordinate)) {
				throw std::invalid_argument("Square is already occupied.");
			}
		}
	}
	return coordinates;
}

vector<pair<int, int>> GBMap::expand(pair<int, int> square) {
	vector<pair<int, int>> coordinates;
	coordinates.push_back({ (square.first << 1), (square.second << 1) });
	coordinates.push_back({ (square.first << 1), (square.second << 1) + 1 });
	coordinates.push_back({ (square.first << 1) + 1, (square.second << 1) + 1 });
	coordinates.push_back({ (square.first << 1) + 1, (square.second << 1) });
	return coordinates;
}

void GBMap::validateSquare(pair<int, int> square) {
	int row = square.first, col = square.second;
	switch (*numPlayers) {
	case 4:
		if (isOnCorner(row, col)) {
			throw std::invalid_argument("Cannot place tiles on corners.");
		}
	case 2:
	case 3:
		if (row < 0 || row >= width() || col < 0 || col >= height()) {
			throw std::invalid_argument("Square is not on board.");
		}
	}
}

bool GBMap::isOnCorner(int row, int col) {
	return (row == 0 || row == height() - 1) && (col == 0 || col == width() - 1);
}

int numberOfNodes(GBMap& map) {
	int nodes;
	auto tokens = map.graph->tokens();
	// Clear map so that all nodes will be counted.
	for (auto& entry : tokens) {
		map.graph->setTokenAt(nullptr, entry.first);
	}
	nodes = map.graph->search((*tokens.begin()).first);
	// Put map back into its original state.
	for (auto& entry : tokens) {
		map.graph->setTokenAt(entry.second, entry.first);
	}
	return nodes / 4;
}

std::ostream& operator<<(std::ostream& stream, const GBMap& map) {
	for (int i = 0; i < map.height(); i++) {
		for (int j = 0; j < map.width(); j++) {
			ResourceToken* resource = static_cast<ResourceToken*>(map.graph->tokenAt({ i, j }));
			if (resource) {
				stream << *resource << '\t';
			}
			else {
				stream << "-\t";
			}
		}
		stream << "\n\n\n";
	}
	return stream;
}