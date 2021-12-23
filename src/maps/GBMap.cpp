#include <sstream>

#include "../Game.h"
#include "GBMap.h"

using std::pair;
using std::string;
using std::vector;

// Statically initialize objects that are frequently used and/or expensive to create.
std::string GBMap::INVALID_NUM_PLAYERS =
        "Number of players must be between " + std::to_string(PLAYERS_MIN) + " and " + std::to_string(PLAYERS_MAX) + ".";

GBMap::GBMap() : GBMap(Game::DEFAULT_NUM_PLAYERS) {
}

GBMap::GBMap(int numPlayers) {
    setNumPlayers(numPlayers);
    graph = TokenGraph::gridOf(DIM, DIM);
}

GBMap::GBMap(const GBMap& other) : GBMap(other.numPlayers) {
    for (auto& entry : *other.graph) {
        AbstractToken* token = entry.second->token;
        graph->setTokenAt(token ? token->clone() : nullptr, entry.first);
    }
}

GBMap::~GBMap() {
    delete graph;
}

void GBMap::setNumPlayers(int numPlayers) {
    if (numPlayers < PLAYERS_MIN || numPlayers > PLAYERS_MAX) {
        throw std::invalid_argument(INVALID_NUM_PLAYERS);
    }
    this->numPlayers = numPlayers;
}

int GBMap::getNumPlayers() const {
    return numPlayers;
}

vector<pair<int, int>> GBMap::corners() const {
    int min = numPlayers == PLAYERS_MIN ? 1 : 0, max = DIM - PLAYERS_MIN >> 1;
    return vector<pair<int, int>> {
        {min, 1}, {min, max - 1}, {max - min, 1}, {max - min, max -1}
    };
}

int GBMap::squaresLeft() const {
    int squares = graph->emptyNodes() >> PLAYERS_MIN, border;
    switch (numPlayers) {
    case PLAYERS_MIN:
        border = (DIM << 1) - PLAYERS_MAX;
        break;
    case PLAYERS_MID:
        border = DIM;
        break;
    case PLAYERS_MAX:
        border = PLAYERS_MAX;
        break;
    }
    return squares - border;
}

void GBMap::setSquare(HarvestTile* tile, pair<int, int> square) {
    if (!tile) {
        throw std::invalid_argument("Cannot place the null tile.");
    }
    for (auto& coordinate : coordinatesOf(square, true)) {
        graph->setTokenAt(tile->tokenize(), coordinate);
    }
    notify();
    delete tile;
}

void GBMap::calculateResources(pair<int, int> from, GatherFacility* resources, ResourceToken* shipment) {
    // Place shipment tile if it has been played.
    if (shipment) {
        for (auto& coordinate : coordinatesOf(from, true)) {
            graph->setTokenAt(new ResourceToken(*shipment), coordinate);
        }
        notify();
    }
    // Perform search for conntected resources starting from the four coordinates in from.
    for (auto& coordinate : coordinatesOf(from)) {
        // Coordinate is occupied.
        if (graph->tokenAt(coordinate)) {
            resources->incrementBy(graph->tokenAt(coordinate)->getType(), graph->search(coordinate));
        }
    }
    // Remove shipment tile.
    if (shipment) {
        for (auto& coordinate : coordinatesOf(from)) {
            graph->removeTokenAt(coordinate);
        }
    }
    graph->cleanupSearch();
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
    return vector<pair<int, int>> {
        {(square.first << 1), (square.second << 1)},
        {(square.first << 1), (square.second << 1) + 1},
        {(square.first << 1) + 1, (square.second << 1)},
        {(square.first << 1) + 1, (square.second << 1) + 1}
    };
}

pair<int, int> GBMap::validateSquare(pair<int, int> square) const {
    if (isOverBoard(square.first, square.second, true)) {
        throw std::invalid_argument("Illegal coordinate.");
    }
    return square;
}

string GBMap::toString() const {
    std::ostringstream stream;
    stream << "       1         2         3         4         5         6         7\n";
    stream << "  ┏━━━━┯━━━━┳━━━━┯━━━━┳━━━━┯━━━━┳━━━━┯━━━━┳━━━━┯━━━━┳━━━━┯━━━━┳━━━━┯━━━━┓\n";
    for (int i = 0, row = 0; i < DIM; i++) {
        stream << "  ┃ ";
        for (int j = 0; j < DIM; j++) {
            if (isOverBoard(i, j)) {
                stream << "░░";
            } else {
                AbstractToken* token = graph->tokenAt({i, j});
                if (token) {
                    stream << *token;
                } else {
                    stream << "--";
                }
            }
            if (j & 1) {
                stream << " ┃ ";
            } else {
                stream << " │ ";
            }
        }
        stream << '\n';
        if (i & 1 && i < DIM - PLAYERS_MIN) {
            stream << "  ┣━━━━┿━━━━╋━━━━┿━━━━╋━━━━┿━━━━╋━━━━┿━━━━╋━━━━┿━━━━╋━━━━┿━━━━╋━━━━┿━━━━┫\n";
            row++;
        } else if (i < DIM - 1) {
            stream << (char)('A' + row);
            stream << " ┠────┼────╂────┼────╂────┼────╂────┼────╂────┼────╂────┼────╂────┼────┨\n";
        }
    }
    stream << "  ┗━━━━┷━━━━┻━━━━┷━━━━┻━━━━┷━━━━┻━━━━┷━━━━┻━━━━┷━━━━┻━━━━┷━━━━┻━━━━┷━━━━┛\n";
    return stream.str();
}

bool GBMap::isOverBoard(int row, int col, bool compressCoordinates) const {
    if (numPlayers == PLAYERS_MAX && isOnCorner(row, col, compressCoordinates)) {
        return true;
    }
    int rowMin = (numPlayers == PLAYERS_MIN ? PLAYERS_MIN : 0) >> (compressCoordinates ? 1 : 0) ;
    int rowMax = (numPlayers == PLAYERS_MIN ? DIM - PLAYERS_MIN - 1 : DIM - 1) >> (compressCoordinates ? 1 : 0);
    int colMin = (numPlayers == PLAYERS_MAX ? 0 : PLAYERS_MIN) >> (compressCoordinates ? 1 : 0);
    int colMax = (numPlayers == PLAYERS_MAX ? DIM - 1 : DIM - PLAYERS_MIN - 1) >> (compressCoordinates ? 1 : 0);
    return row < rowMin || row > rowMax || col < colMin || col > colMax;
}

bool GBMap::isOnCorner(int row, int col, bool compressCoordinates) {
    int min = compressCoordinates ? 1 : PLAYERS_MIN, max = (compressCoordinates ? (DIM - 1) >> 1 : DIM - 1) - min;
    return (row < min || row > max) && (col < min || col > max);
}
