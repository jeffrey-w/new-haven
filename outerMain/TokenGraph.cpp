#include <climits> // For INT_MAX.
#include <queue>

#include "TokenGraph.h"

using std::map;
using std::pair;
using std::queue;
using std::set;

TokenGraph* TokenGraph::gridOf(int height, int width) {
	TokenGraph* graph = new TokenGraph();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			graph->addNode({ i, j });
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pair<int, int> coordinate(i, j);
			if (i < height - 1) {
				graph->addEdge(coordinate, { i + 1, j });
			}
			if (j < width - 1) {
				graph->addEdge(coordinate, { i, j + 1 });
			}
		}
	}
	return graph;
}

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

// TODO need an empty node check/return value
AbstractToken* TokenGraph::tokenAt(pair<int, int> coordinate) {
	return nodeAt(coordinate)->token; // TODO document exception
}

bool TokenGraph::adjacentHolds(pair<int, int> coordinate, int tokenType) { // TODO validate tokenType
	for (auto& adjacent : *nodeAt(coordinate)->adjacents) { // TODO document exception
		if (adjacent->token->getType() == tokenType) {
			return true;
		}
	}
	return false;
}

void TokenGraph::setTokenAt(AbstractToken* token, pair<int, int> coordinate) {
	token->place(); // TODO avoid side effects
	nodeAt(coordinate)->token = token; // TODO document exception
}

int TokenGraph::search(pair<int, int> coordinate) {
	return search(nodeAt(coordinate)); // TODO document exception
}

bool TokenGraph::isBlack(std::pair<int, int> coordinate) {
	return *nodeAt(coordinate)->color == Node::BLACK; // TODO document exception
}

void TokenGraph::cleanupSearch() {
	for (auto& entry : *nodes) {
		*entry.second->color = Node::WHITE;
	}
}

TokenGraph::Node* TokenGraph::nodeAt(pair<int, int> coordinate) {
	return (*nodes)[validateCoordinate(coordinate)];
}

pair<int, int> TokenGraph::validateCoordinate(pair<int, int> coordinate) {
	if (nodes->find(coordinate) == nodes->end()) {
		throw std::exception(); // TODO need richer exception type
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
		for (auto& v : *u->adjacents) {
			if (*v->color == Node::WHITE) {
				*v->color = Node::GRAY;
				*v->distance = *u->distance + 1;
				v->prev = u;
				q.push(v);
				count++;
			}
		}
		*u->color = Node::BLACK;
		u->prev = nullptr; // Otherwise destructor misbehaves.
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

map<pair<int, int>, AbstractToken*>& TokenGraph::tokens() {
	auto tokens = new map<pair<int, int>, AbstractToken*>();
	for (auto& entry : *nodes) {
		tokens->insert({ entry.first, entry.second->token });
	}
	return *tokens;
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
	// This node will be searched if it's connected to source of search.
	if (AbstractToken::areSameType(match, token)) {
		color = new int(WHITE);
	}
	else if (*color == BLACK);
	else {
		color = new int(RED);
	}
	distance = new int(INT_MAX);
	prev = nullptr;
}
