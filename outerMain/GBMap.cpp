#include <vector>

#include "GBMap.h"

using std::map;
using std::pair;
using std::set;
using std::vector;

constexpr int DIM_MIN = 5, DIM_MAX = 7;

GBMap::GBMap(int numPlayers) {
	area = new map<pair<int, int>,Node*>();
	setDimensions(numPlayers);
	build();
}

void GBMap::setDimensions(int numPlayers) {
	switch (numPlayers) {
	case 2:
		*width = DIM_MIN;
		*height = DIM_MIN;
		break;
	case 3:
		*width = DIM_MAX;
		*height = DIM_MIN;
		break;
	case 4:
		*width = DIM_MAX;
		*height = DIM_MAX;
		break;
	default:
		throw new std::exception; // TODO need richer exception type
	}
}

void GBMap::build() {
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			pair<int, int> coord{ i, j };
			addNode(coord);
			if (i < *width - 1) {
				addEdge(coord, { i + 1, j });
			}
			if (j < *height - 1) {
				addEdge(coord, { i, j + 1 });
			}
		}
	}
}

void GBMap::addNode(pair<int, int> coord) {
	area->insert({ coord, new Node() });
}

void GBMap::addEdge(pair<int, int> one, pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adj->insert(n);
	n->adj->insert(m);
}

GBMap::~GBMap() {
	for (auto i : *area) {
		delete i.second;
	}
	delete area;
	area = nullptr;
}

void GBMap::setTile(pair<int, int> coord, HarvestTile* tile) {
	// TODO tile should already be oriented correctly
	nodeAt(coord)->tile = tile;
}

bool GBMap::isTileAvailable(pair<int, int> coord) {
	return nodeAt(coord)->tile;
}

GBMap::Node* GBMap::getOrigin() {
	return nodeAt({ 0, 0 });
}

GBMap::Node* GBMap::nodeAt(pair<int, int> coord) {
	return area->at(validateCoord(coord));
}

pair<int, int> GBMap::validateCoord(pair<int, int> coord) { // TODO do not zero-index
	int x = coord.first, y = coord.second;
	bool xInBounds = x >= 0 && x < *width;
	bool yInBounds = y >= 0 && y < *height;
	if (!(xInBounds && yInBounds)) {
		throw new std::exception; // TODO need richer exception type
	}
	return coord;
}

// Breadth-first search
int GBMap::search(Node* s) {
	int count = 0;
	resetSearchAttributes();
	*s->color = Node::GRAY;
	*s->distance = 0;
	vector<Node*> queue = vector<Node*>();
	queue.push_back(s);
	while (!queue.empty()) {
		Node* u = queue.front();
		for (auto v : *u->adj) {
			if (*v->color == Node::WHITE) {
				*v->color = Node::GRAY;
				*v->distance = *u->distance + 1;
				v->prev = u;
				queue.push_back(v);
				count++;
			}
		}
		*u->color = Node::BLACK;
	}
	return count;
}

void GBMap::resetSearchAttributes() {
	for (auto entry : *area) {
		Node* n = entry.second;
		n->init(n->tile, n->adj);
	}
}

GBMap::Node::Node() {
	init(nullptr, nullptr);
}

GBMap::Node::~Node() {
	delete tile;
	delete adj;
	delete color;
	delete distance;
	delete prev;
	tile = nullptr;
	adj = nullptr;
	color = nullptr;
	distance = nullptr;
	prev = nullptr;
}

void GBMap::Node::init(HarvestTile* tile, set<Node*>* adj) {
	this->tile = tile;
	this->adj = (adj) ? adj : new set<Node*>();
	color = new int(WHITE);
	distance = new int(INT_MAX);
	prev = nullptr;
}
