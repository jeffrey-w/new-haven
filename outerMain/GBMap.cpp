#include <climits>
#include <queue>

#include "GBMap.h"

using std::map;
using std::pair;
using std::queue;
using std::set;
using std::vector;

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

void GBMap::addNode(pair<int, int> coord) {
	area->insert({ coord, new Node() });
}

void GBMap::addEdge(pair<int, int> one, pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adjacents->insert(n);
	n->adjacents->insert(m);
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

// Breadth-first search
int GBMap::search(Node* s) {
	int count = 1;
	resetSearchAttributes();
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

void GBMap::resetSearchAttributes() {
	for (auto entry : *area) {
		Node* n = entry.second;
		n->init(n->resource, n->adjacents);
	}
}

GBMap::Node::Node() {
	init(nullptr, nullptr);
}

GBMap::Node::~Node() {
	delete resource;
	delete adjacents;
	delete color;
	delete distance;
	delete prev;
}

void GBMap::Node::init(Resource* resource, set<Node*>* adjacents) {
	this->resource = resource;
	this->adjacents = (adjacents) ? adjacents : new set<Node*>();
	color = new int(WHITE);
	distance = new int(INT_MAX);
	prev = nullptr;
}
