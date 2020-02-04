#pragma once

#include <map>
#include <set>

#include "Player.h" // TODO as of yet unused

using std::map;
using std::pair;
using std::set;
using Coord = pair<int, int>;

class Node {

	friend class GBMap;

private:

	const int WHITE = 0, GRAY = 1, BLACK = 2;

	HarvestTile* tile;
	set<Node*>* adj;
	bool* visited;
	
	// Search attributes
	int* color;
	int* distance;
	Node* prev;

	Node();
	~Node();

};

class GBMap {

private:

	map<Coord,Node*>* area;

public:

	GBMap(int);
	~GBMap();
	void setSpace(int, int, int, HarvestTile*);
	bool spaceIsEmpty(int, int);

private:
	
	void addNode(Coord);
	void addEdge(Coord, Coord);
	Node* nodeAt(Coord);
	void search(Node*);
};
