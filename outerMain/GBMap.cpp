#include <climits>
#include <queue>

#include "GBMap.h"

using std::map;
using std::pair;
using std::queue;
using std::set;
using std::vector;

GBMap::GBMap() : GBMap(DEFAULT_NUM_PLAYERS) {}

GBMap::GBMap(int numPlayers) {
	this->numPlayers = new int(validateNumPlayers(numPlayers));
	area = new map<pair<int, int>, Node*>();
}

int GBMap::validateNumPlayers(int numPlayers) {
	if ((numPlayers == 2 || numPlayers == 3 || numPlayers == 4)) {
		throw new std::exception(); // TODO need richer exception type
	}
	return numPlayers;
}

GBMap::~GBMap() {
	delete numPlayers;
	delete area;
}

void GBMap::setSquare(pair<int, int> coord, HarvestTile* tile) {
	for (auto node : nodeSet(coord)) {
		node->resource = tile->next();
	}
}

void GBMap::addNode(pair<int, int> coord) {
	area->insert({ coord, new Node() });
}

void GBMap::addEdge(pair<int, int> one, pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adjacents->insert(n);
	n->adjacents->insert(m);
}

vector<GBMap::Node*> GBMap::nodeSet(pair<int, int> square) {
	pair<int, int> rowLimits = expand(square.first, height());
	pair<int, int> colLimits = expand(square.second, width());
	vector<Node*> nodes(HarvestTile::NUM_RESOURCES);
	for (int i = rowLimits.first; i <= rowLimits.second; i++) {
		for (int j = colLimits.first; j <= colLimits.second; j++) {
			nodes.push_back(nodeAt({ i, j }));
		}
	}
	return nodes;
}

std::pair<int, int> GBMap::expand(int coordinate, int dimension) {
	if (coordinate < 0 || coordinate >= dimension) {
		throw new std::exception(); // TODO need richer exception type
	}
	if (coordinate == 0) {
		return { 0, 1 };
	}
	pair<int, int> prev = expand(coordinate - 1, dimension);
	return { prev.first + 2, prev.second + 2 };
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

GBMap::Node* GBMap::nodeAt(std::pair<int, int> coordinate) {
	return area->at(coordinate);
}

// Breadth-first search
int GBMap::search(Node* s) {
	int count = 1;
	resetSearchAttributes(s->resource);
	*s->color = Node::GRAY;
	*s->distance = 0;
	queue<Node*> q = queue<Node*>();
	q.push(s);
	while (!q.empty()) {
		Node* u = q.front();
		for (auto v : *u->adjacents) {
			if (*v->color == Node::WHITE) {
				*v->color = Node::GRAY;
				*v->distance = *u->distance + 1;
				v->prev = u;
				q.push(v);
				count++;
			}
		}
		*u->color = Node::BLACK;
		// u->prev = nullptr; TODO is this needed?
		q.pop();
	}
	return count;
}

void GBMap::resetSearchAttributes(Resource* match) {
	for (auto entry : *area) {
		Node* n = entry.second;
		n->init(n->resource, match, n->adjacents);
	}
}

GBMap::Node::Node() {
	init(nullptr, nullptr, nullptr);
}

GBMap::Node::~Node() {
	delete resource;
	delete adjacents;
	delete color;
	delete distance;
	delete prev;
}

void GBMap::Node::init(Resource* resource, Resource* match, set<Node*>* adjacents) {
	this->resource = resource;
	this->adjacents = (adjacents) ? adjacents : new set<Node*>();
	if (Resource::equals(match, resource)) {
		color = new int(WHITE);
	}
	else {
		color = new int(BLACK);
	}
	distance = new int(INT_MAX);
	prev = nullptr;
}
