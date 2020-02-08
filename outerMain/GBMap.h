#pragma once

#include <map>
#include <set>

#include "HarvestTile.h"

class GBMap {

public:

	GBMap(int);
	~GBMap();
	void setTile(std::pair<int, int>, HarvestTile*);
	bool isTileAvailable(std::pair<int, int>);

private:

	class Node {

	public:

		static const int WHITE = 0, GRAY = 1, BLACK = 2;

		HarvestTile* tile;
		std::set<Node*>* adj;

		// Search attributes
		int* color;
		int* distance;
		Node* prev;

		Node();
		~Node();
		void init(HarvestTile*, std::set<Node*>*);

	};

	int* width;
	int* height;
	std::map<std::pair<int, int>,Node*>* area;

	void setDimensions(int);
	void build();
	void addNode(std::pair<int, int>);
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	Node* getOrigin();
	Node* nodeAt(std::pair<int, int>);
	std::pair<int, int> validateCoord(std::pair<int, int>);
	int search(Node*);
	void resetSearchAttributes();

};
