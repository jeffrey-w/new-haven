#include "GBMap.h"

using Nodes = map<Coord,Node*>;

Node::Node() {
	tile = nullptr;
	adj = new set<Node*>();
	visited = new bool(false);
	color = new int(WHITE);
	distance = new int(INFINITY); // TOOD float to int is dangerous
	prev = nullptr;
}

Node::~Node() {
	delete tile;
	tile = nullptr;
	delete adj;
	adj = nullptr;
	delete visited;
	visited = nullptr;
	delete color;
	color = nullptr;
	delete distance;
	distance = nullptr;
	delete prev;
	prev = nullptr;
}

GBMap::GBMap(int numPlayers) {
	area = new map<Coord,Node*>();
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
	default:
		throw new std::exception; // TODO need richer exception type
	}
	// TODO dispatch to node and edge creation functions
}

GBMap::~GBMap() {
	for (Nodes::iterator i = area->begin(); i != area->end(); i++) {
		delete i->second;
	}
	delete area;
	area = nullptr;
}

void GBMap::setSpace(Coord coord, HarvestTile* tile, int orientation) {
	tile->changeTileOrientation(orientation);
	nodeAt(validateCoord(coord))->tile = tile;
}

bool GBMap::spaceIsEmpty(Coord coord) {
	return nodeAt(validateCoord(coord))->tile == nullptr;
}

void GBMap::addNode(Coord coord) {
	area->insert({ coord, new Node() });
}

void GBMap::addEdge(Coord one, Coord two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adj->insert(n);
	n->adj->insert(m);
}

Node* GBMap::getOrigin() {
	return nodeAt({ 0, 0 });
}

Node* GBMap::nodeAt(Coord coord) {
	return area->at(coord);
}

void GBMap::search(Node*) {
	// TODO
}

Coord GBMap::validateCoord(Coord coord) {
	int row = coord.first, col = coord.second;
	bool xInBounds = col >= 0 && col < *colMax;
	bool yInBounds = row >= 0 && row < *rowMax;
	if (!(xInBounds && yInBounds)) {
		throw new std::exception; // TODO need richer exception type
	}
	return coord;
}
