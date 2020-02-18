#pragma once

#include <map>
#include <set>

#include "HarvestTile.h"
#include "Resource.h"

class GBMap {

	static constexpr int DIM_MIN = 5, DIM_MAX = 7;

public:

	GBMap(int);
	~GBMap();
	void setTile(std::pair<int, int>, HarvestTile*);
	bool isTileAvailable(std::pair<int, int>);
	int search(std::pair<int, int>);
	void display();

private:

	class Node {

	public:

		static const int WHITE = 0, GRAY = 1, BLACK = 2;

		Resource* tile; // TODO rename this
		std::set<Node*>* adj;

		// Search attributes
		int* color;
		int* distance;
		Node* prev;

		Node();
		~Node();
		void init(HarvestTile*, std::set<Node*>*);

	};

	int* numPlayers;
	std::map<std::pair<int, int>, Node*>* area;

	static int validateNumPlayers(int);
	void addNode(std::pair<int, int>);
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	Node* getOrigin();
	Node* nodeAt(std::pair<int, int>);
	std::pair<int, int> validateCoord(std::pair<int, int>);
	int search(Node*);
	void resetSearchAttributes();

};
