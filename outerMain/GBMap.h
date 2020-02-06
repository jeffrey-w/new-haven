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

	static const int WHITE = 0, GRAY = 1, BLACK = 2;

	HarvestTile* tile;
	set<Node*>* adj;
	
	// Search attributes
	int* color;
	int* distance;
	Node* prev;

	Node();
	~Node();

};

class GBMap {

private:

	int* rowMax;
	int* colMax;
	map<Coord,Node*>* area;

public:

	GBMap(int);
	~GBMap();
	void setTile(Coord, HarvestTile*);
	bool isTileAvailable(Coord);

private:
	
	void addNode(Coord);
	void addEdge(Coord, Coord);
	Node* getOrigin();
	Node* nodeAt(Coord);
	Coord validateCoord(Coord coord);
	void search(Node*);
};
