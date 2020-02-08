#pragma once

#include <map>
#include <set>

#include "HarvestTile.h"

class GBMap {

public:

	GBMap(int);
	~GBMap();
	void set_tile_above_node(int, HarvestTile*);
	bool is_node_available(int);
	int search(std::pair<int, int>);
	void display();

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
	std::map<int,Node*>* playing_board;

	int* number_of_nodes_on_playing_board;

	void generate_map_size(int);
	void build();
	void addNode(int);
	void addEdge(int, int);
	Node* getOrigin();
	Node* nodeAt(int);
	int validate_position(int);
	int search(Node*);
	void resetSearchAttributes();

};
