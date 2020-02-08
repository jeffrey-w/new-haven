#include <vector>

#include "GBMap.h"

using std::map;
using std::pair;
using std::set;
using std::vector;

Node::Node() {
	tile = nullptr;
	adj = new set<Node*>();
	color = new int(WHITE);
	distance = new int(INFINITY); // TOOD float to int is dangerous
	prev = nullptr;
}

Node::~Node() {
	delete tile;
	tile = nullptr;
	delete adj;
	adj = nullptr;
	delete color;
	color = nullptr;
	delete distance;
	distance = nullptr;
	delete prev;
	prev = nullptr;
}

GBMap::GBMap(int numPlayers) {
	area = new map<pair<int, int>,Node*>();
	switch (numPlayers) { // TODO avoid magic constants
	case 2:
		*rowMax = 5;
		*colMax = 5;
		break;
	case 3:
		*rowMax = 7;
		*colMax = 5;
		break;
	case 4:
		*rowMax = 7;
		*colMax = 7;
		break;
	default:
		throw new std::exception; // TODO need richer exception type
	}
	// TODO dispatch to node and edge creation functions
}

GBMap::~GBMap() {
	for (map<pair<int, int>, Node*>::iterator i = area->begin(); i != area->end(); i++) {
		delete i->second;
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

void GBMap::addNode(pair<int, int> coord) {
	area->insert({ coord, new Node() });
}

void GBMap::addEdge(pair<int, int> one, pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adj->insert(n);
	n->adj->insert(m);
}

Node* GBMap::getOrigin() {
	return nodeAt({ 0, 0 });
}

Node* GBMap::nodeAt(pair<int, int> coord) {
	return area->at(validateCoord(coord));
}

pair<int, int> GBMap::validateCoord(pair<int, int> coord) { // TODO do not zero-index
	int row = coord.first, col = coord.second;
	bool xInBounds = col >= 0 && col < *colMax;
	bool yInBounds = row >= 0 && row < *rowMax;
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
		set<Node*>* list = u->adj;
		for (set<Node*>::iterator i = list->begin(); i != list->end(); i++) {
			Node* v = *i;
			if (*v->color == Node::WHITE) {
				count++;
				*v->color = Node::GRAY;
				*v->distance = *u->distance + 1;
				v->prev = u;
				queue.push_back(v);
			}
		}
		*u->color = Node::BLACK;
	}
	return count;
	// TODO reset Node search attributes for next search
}

void GBMap::validate() {
	if (search(getOrigin()) != *rowMax * *colMax) {
		throw new std::exception(); // TODO need richer exception type
	}
}
