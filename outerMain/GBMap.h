#pragma once

#include <map>
#include <set>
#include <vector>

#include "HarvestTile.h"
#include "Resource.h"

class GBMap {

	static constexpr int DIM_MIN = 5, DIM_MAX = 7;

public:

	GBMap(int);
	~GBMap();
	void setSquare(std::pair<int, int>, HarvestTile*);

private:

	class Node {

	public:

		static constexpr int WHITE = 0, GRAY = 1, BLACK = 2;

		Resource* resource; // TODO rename this
		std::set<Node*>* adjacents;

		// Search attributes
		int* color;
		int* distance;
		Node* prev;

		Node();
		~Node();
		void init(Resource*, Resource*, std::set<Node*>*);

	};

	int* numPlayers;
	std::map<std::pair<int, int>, Node*>* area;

	static int validateNumPlayers(int);

	void addNode(std::pair<int, int>);
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	std::vector<Node*> nodeSet(std::pair<int, int>);
	std::pair<int, int> expand(int, int);
	int height();
	int width();
	Node* nodeAt(std::pair<int, int>);
	int search(Node*);
	void resetSearchAttributes(Resource*);

};
