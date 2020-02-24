#pragma once

#include <map>
#include <set>

#include "AbstractToken.h"

class TokenGraph {

	class Node;

public:

	// Static factory method.
	static TokenGraph* gridOf(int, int);

	TokenGraph();
	TokenGraph(TokenGraph&) = delete; // Supress copy constructor.
	~TokenGraph();
	void addNode(std::pair<int, int>);
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	AbstractToken* tokenAt(std::pair<int, int>);
	bool isBlack(std::pair<int, int> coordinate);
	bool adjacentHolds(std::pair<int, int>, int);
	void setTokenAt(AbstractToken*, std::pair<int, int>);
	int search(std::pair<int, int>);
	std::map<std::pair<int, int>, AbstractToken*>& tokens();

private:

	class Node {

	public:

		static constexpr int WHITE = 0, GRAY = 1, BLACK = 2, RED = 3;

		AbstractToken* token;
		std::set<Node*>* adjacents;

		// Search Attributes
		int* color;
		int* distance;
		Node* prev;

		Node();
		Node(Node&) = delete;
		~Node();
		void init(AbstractToken*, AbstractToken*, std::set<Node*>*);

	};

	std::map<std::pair<int, int>, Node*>* nodes;

	Node* nodeAt(std::pair<int, int>);
	std::pair<int, int> validateCoordinate(std::pair<int, int>);
	int search(Node*);
	void resetSearchAttributes(AbstractToken*);

};

