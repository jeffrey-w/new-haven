#include <queue>

#include "VGMap.h"

using std::map;
using std::pair;
using std::queue;

VGMap::VGMap() {
	nodes = new map<pair<int, int>, Node*>();
	build();
}

// TODO need to number circles
void VGMap::build() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			addNode({ i, j });
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			pair<int, int> coordinate(i, j);
			if (i < HEIGHT - 1) {
				addEdge(coordinate, { i + 1, j });
			}
			if (j < WIDTH - 1) {
				addEdge(coordinate, { i , j + 1 });
			}
		}
	}
}

void VGMap::addNode(std::pair<int, int> coordinate) {
	nodes->insert({ coordinate, new Node() });
}

void VGMap::addEdge(std::pair<int, int> one, std::pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adjacents->insert(n);
	n->adjacents->insert(m);
}

VGMap::~VGMap() {
	delete nodes;
}

void VGMap::setCicle(std::pair<int, int> circle, Building* building) {
	nodeAt(circle)->building = building;
}

VGMap::Node* VGMap::nodeAt(std::pair<int, int> coordinate) {
	return nodes->at(validateCoordinate(coordinate));
}

std::pair<int, int> VGMap::validateCoordinate(std::pair<int, int> coordinate) {
	if (nodes->find(coordinate) == nodes->end()) {
		throw new std::exception(); // TODO need richer exception type
	}
	return coordinate;
}

// Breadth-first search
int VGMap::search(Node* s) {
	int count = 1;
	resetSearchAttributes(s->building);
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
		u->prev = nullptr;
		q.pop();
	}
	return count;
}

void VGMap::resetSearchAttributes(Building* match) {
	for (auto entry : *nodes) {
		Node* n = entry.second;
		n->init(n->building, match, n->adjacents);
	}
}
