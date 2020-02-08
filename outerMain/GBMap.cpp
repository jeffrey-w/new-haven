#include <queue>

#include "GBMap.h"

using std::map;
using std::pair;
using std::queue;
using std::set;
using std::cout;
using std::endl;

const int SMALL_MAP = 25, MEDIUM_MAP = 35, LARGE_MAP = 45; // constexpr?

GBMap::GBMap(int numPlayers) {
	number_of_nodes_on_playing_board = new int();
	playing_board = new map<int, Node*>;
	build();

	generate_map_size(numPlayers);
}

void GBMap::generate_map_size(int numPlayers) {
	switch (numPlayers) {
	case 2:
		*number_of_nodes_on_playing_board = SMALL_MAP;
		break;
	case 3:
		*number_of_nodes_on_playing_board = MEDIUM_MAP;
		break;
	case 4:
		*number_of_nodes_on_playing_board = LARGE_MAP;
		break;
	default:
		throw new std::exception(); // TODO need richer exception type
	}
}

void GBMap::build() {

	addNode(1);
	addNode(5);
	addNode(21);
	addNode(25);

}

void GBMap::addNode(int position) {
	playing_board->insert({ position, new Node() });
}

void GBMap::addEdge(int one, int two) {
	Node* m = nodeAt(one);
	Node* n = nodeAt(two);
	m->adj->insert(n);
	n->adj->insert(m);
}

GBMap::~GBMap() {
	for (auto i : *playing_board) {
		delete i.second;
	}
	delete playing_board;
	playing_board = nullptr;
}

void GBMap::set_tile_above_node(int position, HarvestTile* tile) {
	// TODO tile should already be oriented correctly
	nodeAt(position)->tile = tile;
}

bool GBMap::is_node_available(int position) {
	return nodeAt(position)->tile;
}


GBMap::Node* GBMap::getOrigin() {
	return nodeAt(1);
}

GBMap::Node* GBMap::nodeAt(int position) {
	return playing_board->at(validate_position(position));  
}

int GBMap::validate_position(int position) { 
	
	if (!(position > 0 && position <= *number_of_nodes_on_playing_board)) {
		cout << "invalid position" << endl;
		//throw new std::exception(); 
	}
	return position;
}

//int GBMap::search(pair<int, int> coord) {
//	return search(nodeAt(coord));
//}


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
		q.front();
		for (auto v : *u->adj) {
			if (*v->color == Node::WHITE) {
				*v->color = Node::GRAY;
				*v->distance = *u->distance + 1;
				v->prev = u;
				q.push(v);
				count++;
			}
		}
		*u->color = Node::BLACK;
		q.pop();
	}
	return count;
}

void GBMap::resetSearchAttributes() {
	for (auto entry : *playing_board) {
		Node* n = entry.second;
		n->init(n->tile, n->adj);
	}
}

//void GBMap::display() {
//	for (int i = 0; i < *width; i++) {
//		for (int j = 0; j < *height; j++) {
//			HarvestTile* tile = nodeAt({ i, j })->tile;
//			if (tile) {
//				std::cout << tile << '\t';
//			}
//			else {
//				std::cout << "-\t";
//			}
//		}
//		std::cout << "\n\n";
//	}
//}

GBMap::Node::Node() {
	init(nullptr, nullptr);
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

void GBMap::Node::init(HarvestTile* tile, set<Node*>* adj) {
	this->tile = tile;
	this->adj = (adj) ? adj : new set<Node*>();
	color = new int(WHITE);
	distance = new int(INT_MAX);
	prev = nullptr;
}
