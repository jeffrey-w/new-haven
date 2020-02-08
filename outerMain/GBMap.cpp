#include <vector>

#include "GBMap.h"

using std::map;
using std::pair;
using std::set;
using std::vector;

GBMap::GBMap(int numPlayers) {
	area = new map<pair<int, int>,Node*>();
	setDimensions(numPlayers);
	build();
}

void GBMap::setDimensions(int numPlayers) {
	switch (numPlayers) { // TODO avoid magic constants
	case 2:
		*width = 5;
		*height = 5;
		break;
	case 3:
		*width = 7;
		*height = 5;
		break;
	case 4:
		*width = 7;
		*height = 7;
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
	return nodeAt(coord)->tile == nullptr;
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
	*s->color = Node::GRAY;
	*s->distance = 0;
	s->prev = nullptr; // TODO is this needed?
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
	// TODO reset Node search attributes for next search
}

GBMap::Node::Node() {
	tile = nullptr;
	adj = new set<Node*>();
	color = new int(WHITE);
	distance = new int(INT32_MAX);
	prev = nullptr;
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
