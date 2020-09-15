#include <queue>
#include <stdexcept>

#include "TokenGraph.h"

using std::map;
using std::pair;
using std::queue;
using std::set;

TokenGraph* TokenGraph::gridOf(int height, int width) {
    TokenGraph* graph = new TokenGraph();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Add nodes before edges to avoid dereferencing null pointers.
            graph->addNode({i, j});
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pair<int, int> coordinate(i, j);
            if (i < height - 1) {
                graph->addEdge(coordinate, {i + 1, j});
            }
            if (j < width - 1) {
                graph->addEdge(coordinate, {i, j + 1});
            }
        }
    }
    return graph;
}

TokenGraph::TokenGraph() {
    searches = 0;
    for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
        types[i] = 0;
    }
}

TokenGraph::~TokenGraph() {
    for (auto& node : nodes) {
        delete node.second;
    }
}

void TokenGraph::addNode(pair<int, int> coordinate) {
    nodes[coordinate] = new Node();
}

void TokenGraph::addEdge(pair<int, int> one, pair<int, int> two) {
    Node* m = nodeAt(one);
    Node* n = nodeAt(two);
    m->adjacents.insert(n);
    n->adjacents.insert(m);
}

bool TokenGraph::emptyAt(pair<int, int> coordinate) {
    return !nodeAt(coordinate)->token;
}

size_t TokenGraph::emptyNodes() const {
    int occupied = 0;
    for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
        occupied += types[i];
    }
    return nodes.size() - occupied;
}

AbstractToken* TokenGraph::tokenAt(pair<int, int> coordinate) const {
    return nodeAt(coordinate)->token;
}

bool TokenGraph::hasType(int type) const {
    return types[AbstractToken::validateType(type)];
}

bool TokenGraph::adjacentHolds(pair<int, int> coordinate, int type) const {
    for (auto& adjacent : nodeAt(coordinate)->adjacents) {
        if (adjacent->token && adjacent->token->getType() == type) {
            return true;
        }
    }
    return false;
}

void TokenGraph::setTokenAt(AbstractToken* token, pair<int, int> coordinate) {
    Node* n = nodeAt(coordinate);
    if (n->token) {
        types[n->token->getType()]--;
    }
    if (token) {
        types[token->getType()]++;
    }
    n->token = token;
}

void TokenGraph::removeTokenAt(pair<int, int> coordinate) {
    Node* n = nodeAt(coordinate);
    if (n->token) {
        types[n->token->getType()]--;
    }
    delete n->token;
    n->token = nullptr;
}

int TokenGraph::search(pair<int, int> coordinate) {
    return search(nodeAt(coordinate));
}

TokenGraph::Node* TokenGraph::nodeAt(pair<int, int> coordinate) const {
    return nodes.at(validateCoordinate(coordinate));
}

pair<int, int> TokenGraph::validateCoordinate(pair<int, int> coordinate) const {
    if (!nodes.count(coordinate)) {
        throw std::invalid_argument("Coordinate is not on graph.");
    }
    return coordinate;
}

int TokenGraph::search(Node* s) {
    int count = 1;
    setupSearchAttributes(s->token);
    s->color = Node::GRAY;
    queue<Node*> q;
    q.push(s);
    while (!q.empty()) {
        Node* u = q.front();
        for (auto& v : u->adjacents) {
            if (v->color == Node::WHITE) {
                v->color = Node::GRAY;
                q.push(v);
                count++;
            }
        }
        u->color = Node::BLACK;
        q.pop();
    }
    if (!(++searches & AbstractToken::NUM_TYPES - 1)) {
        cleanupSearch();
    }
    return count;
}

void TokenGraph::setupSearchAttributes(AbstractToken* match) {
    for (auto& entry : nodes) {
        Node* n = entry.second;
        // Don't search Nodes more than once
        if (n->color != Node::BLACK) {
            n->init(n->token, match);
        }
    }
}

void TokenGraph::cleanupSearch() {
    for (auto& entry : nodes) {
        entry.second->color = Node::WHITE;
    }
}

map<pair<int, int>, AbstractToken*> TokenGraph::tokens() const {
    map<pair<int, int>, AbstractToken*> tokens;
    for (auto& entry : nodes) {
        tokens.insert({entry.first, entry.second->token});
    }
    return tokens;
}

TokenGraph::Node::Node() {
    init(nullptr, nullptr);
}

TokenGraph::Node::~Node() {
    delete token;
}

void TokenGraph::Node::init(AbstractToken* token, AbstractToken* match) {
    this->token = token;
    // This node will be searched if it's connected to source of search.
    if (AbstractToken::areSameType(match, token)) {
        color = WHITE;
    } else {
        color = RED;
    }
}
