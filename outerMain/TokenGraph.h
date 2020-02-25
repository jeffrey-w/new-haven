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
	// Suppress copy constructor.
	TokenGraph(TokenGraph&) = delete;
	~TokenGraph();
	void addNode(std::pair<int, int>);
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	AbstractToken* tokenAt(std::pair<int, int>);
	bool adjacentHolds(std::pair<int, int>, int);
	void setTokenAt(AbstractToken*, std::pair<int, int>);
	int search(std::pair<int, int>);
	bool isSearched(std::pair<int, int> coordinate);
	void markRow(int);
	void markCol(int);
	void cleanupSearch();
	std::map<std::pair<int, int>, AbstractToken*>& tokens();

private:

	class Node {

	public:

		static constexpr int WHITE = 0, GRAY = 1, BLACK = 2, RED = 3, YELLOW = 4;

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
	void setupSearchAttributes(AbstractToken*);

};

