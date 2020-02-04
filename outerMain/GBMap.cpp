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
	// TODO switch on numPlayers
}

GBMap::~GBMap() {
	for (Nodes::iterator i = area->begin(); i != area->end(); i++) {
		delete i->second;
	}
	delete area;
	area = nullptr;
}

void GBMap::setSpace(int row, int col, int orientation, HarvestTile* tile) {
	// TODO need to validate row and col
	tile->changeTileOrientation(orientation);
	nodeAt(Coord(row, col))->tile = tile;
}

bool GBMap::spaceIsEmpty(int row, int col) {
	// TODO need to validate row and col
	return nodeAt(Coord(row, col))->tile == nullptr;
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

Node* GBMap::nodeAt(Coord coord) {
	return area->at(coord);
}

void GBMap::search(Node*) {
	// TODO
}
