#include <climits> // For INT_MAX.
#include <queue>

#include "TokenGraph.h"

using std::map;
using std::pair;
using std::queue;
using std::set;

TokenGraph::TokenGraph() {
	nodes = new map<pair<int, int>, Node*>();
}

TokenGraph::~TokenGraph() {
	delete nodes;
}

void TokenGraph::addNode(pair<int, int> coordinate) {
	(*nodes)[coordinate] = new Node();
}

void TokenGraph::addEdge(pair<int, int> one, pair<int, int> two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adjacents->insert(n);
	n->adjacents->insert(m);
}

AbstractToken* TokenGraph::tokenAt(pair<int, int> coordinate) {
	return nodeAt(coordinate)->token; // TODO document exception
}

void TokenGraph::setTokenAt(AbstractToken* token, pair<int, int> coordinate) {
	nodeAt(coordinate)->token = token; // TODO document exception
}


int TokenGraph::search(std::pair<int, int> coordinate) {
	return search(nodeAt(coordinate)); // TODO document exception
}

TokenGraph::Node* TokenGraph::nodeAt(pair<int, int> coordinate) {
	return (*nodes)[validateCoordinate(coordinate)];
}

pair<int, int> TokenGraph::validateCoordinate(pair<int, int> coordinate) {
	if (nodes->find(coordinate) == nodes->end()) {
		throw new std::exception(); // TODO need richer exception type
	}
	return coordinate;
}

int TokenGraph::search(Node* s) {
	int count = 1;
	resetSearchAttributes(s->token);
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

void TokenGraph::resetSearchAttributes(AbstractToken* match) {
	for (auto entry : *nodes) {
		Node* n = entry.second;
		n->init(n->token, match, n->adjacents);
	}
}


TokenGraph::Node::Node() {
	init(nullptr, nullptr, nullptr);
}

TokenGraph::Node::~Node() {
	delete token;
	delete adjacents;
	delete color;
	delete distance;
	delete prev;
}

void TokenGraph::Node::init(AbstractToken* token, AbstractToken* match, set<Node*>* adjacents) {
	this->token = token;
	this->adjacents = (adjacents) ? adjacents : new set<Node*>();
	if (AbstractToken::areSameType(match, token)) {
		color = new int(WHITE);
	}
	else {
		color = new int(BLACK);
	}
	distance = new int(INT_MAX);
	prev = nullptr;
}
