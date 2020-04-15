#include <sstream>

#include "../Game.h"
#include "../util/Debug.h"
#include "GBMap.h"

using std::pair;
using std::string;
using std::vector;

// Statically initialize objects that are frequently used and/or expensive to create.
std::string GBMap::INVALID_NUM_PLAYERS = "Number of players must be between "
	+ std::to_string(PLAYERS_MIN) + " and " + std::to_string(PLAYERS_MAX) + ".";

GBMap::GBMap() : GBMap(Game::DEFAULT_NUM_PLAYERS) {}

GBMap::GBMap(int numPlayers) {
	setNumPlayers(numPlayers);
	graph = TokenGraph::gridOf(height(), width());
}

void GBMap::setNumPlayers(int numPlayers) {
	if (numPlayers < PLAYERS_MIN || numPlayers > PLAYERS_MAX) {
		throw std::invalid_argument(INVALID_NUM_PLAYERS);
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

std::vector<std::pair<int, int>> GBMap::corners() const {
	int lower = *numPlayers == PLAYERS_MAX ? 1 : 0;
	int rows = (height() - 1) >> 1, cols = (width() - 1) >> 1;
	vector <pair<int, int>> corners;
	corners.push_back({ 0, lower });
	corners.push_back({ 0, cols  - lower});
	corners.push_back({ rows, lower});
	corners.push_back({ rows, cols - lower});
	return corners;
}

int GBMap::squaresLeft() const {
	int squares = graph->emptyNodes();
	// Don't count corner squares.
	if (*numPlayers == PLAYERS_MAX) {
		squares -= PLAYERS_MAX << PLAYERS_MIN;
	}
	return squares >> PLAYERS_MIN;
}

void GBMap::setSquare(HarvestTile* tile, pair<int, int> square) {
	if (!tile) {
		throw std::invalid_argument("Cannot place the null tile.");
	}
	for (auto& coordinate : coordinatesOf(square, true)) {
		graph->setTokenAt(tile->tokenize(), coordinate);
	}
	delete tile;
	notify();
}

void GBMap::calculateResources(pair<int, int> from, GatherFacility* resources,
		ResourceToken* shipment) {
	// Place shipment tile if it has been played.
	if (shipment) {
		for (auto& coordinate : coordinatesOf(from, true)) {
			graph->setTokenAt(new ResourceToken(*shipment), coordinate);
		}
		notify();
	}
	// Perform search for conntected resources starting from the four coordinates in from.
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

vector<pair<int, int>> GBMap::coordinatesOf(pair<int, int> square, bool ensureEmpty) const {
	vector<pair<int, int>> coordinates = expand(validateSquare(square));
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

pair<int, int> GBMap::validateSquare(pair<int, int> square) const {
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
		break;
	default:
		throw std::logic_error("FATAL ERROR: numPlayers has unexpected value.");
	}
	return square;
}

bool GBMap::isOnCorner(int row, int col) const {
	return (row == 0 || row == height() - 1) && (col == 0 || col == width() - 1);
}

string* GBMap::toString() const {
	int coordinate = 0;
	std::ostringstream stream;
	stream << '\t';
	for (int i = 0; i < width(); i++) {
		if (i & 1) {
			stream << '\t';
		}
		else {
			stream << coordinate++ << '\t';
		}
	}
	coordinate = 0;
	stream << "\n\n\n";
	for (int i = 0; i < height(); i++) {
		if (i & 1) {
			stream << '\t';
		}
		else {
			stream << coordinate++ << '\t';
		}
		for (int j = 0; j < width(); j++) {
			ResourceToken* resource = static_cast<ResourceToken*>(graph->tokenAt({ i, j }));
			if (resource) {
				stream << *resource << '\t';
			}
			else {
				stream << "-\t";
			}
		}
		stream << "\n\n\n";
	}
	return new string(stream.str());
}
