#pragma once

#include <bitset>
#include <map>
#include <set>

#include "../pieces/AbstractToken.h"

// A graph that holds AbstractTokens.
class TokenGraph {

public:

	static constexpr int NUM_TYPES = 4;

	// Static factory method: returns a TokenGraph configured as a grid of the specified height
	// and width.
	static TokenGraph* gridOf(int, int);

	// Constructs a new TokenGraph object.
	TokenGraph();
	// Suppress copy constructor.
	TokenGraph(const TokenGraph&) = delete;
	// Destroys this TokenGraph.
	~TokenGraph();
	// Adds a node to this TokenGraph at the specified coordinate.
	void addNode(std::pair<int, int>);
	// Adds an edge incident on the Nodes at the specified coordinates of this TokenGraph. Throws
	// an exception if either of the specified coordinates does not reference a Node of this
	// TokenGraph.
	void addEdge(std::pair<int, int>, std::pair<int, int>);
	// Returns the number of empty nodes on this TokenGraph.
	int emptyNodes() const;
	// Returns the Token occupying this TokenGraph at the specified coordinate, or null if the Node
	// is empty. Throws an exceptionif the specified coordinate does not referecnce a Node of this
	// TokenGraph.
	AbstractToken* tokenAt(std::pair<int, int>) const;
	// Returns true iff this TokenGraph contains a Token of the specified type.
	bool hasType(int) const;
	// Returns true iff any of the Nodes of this TokenGraoh that are adjacent to the one at the
	// specified coordinate contain a Token of the specified type. Throws an exception if the
	// specified coordinate does not reference a Node of this TokenGraph.
	bool adjacentHolds(std::pair<int, int>, int) const;
	// Places the specified Token into the Node at the specified coordinate of this TokenGraph. The
	// status of the specified Token will be placed after calls to this method return. Throws an
	// exception if the specified coordinate does not reference a Node of this TokenGraph.
	void setTokenAt(AbstractToken*, std::pair<int, int>);
	// Removes the Token occupying the node at the specified coordinate of this. Throws an
	// exception if the specifeid coordinate does not reference a Node of this TokenGraph.
	void removeTokenAt(std::pair<int, int>);
	// Initiates a breadth-first search of this TokenGraph from the Node at the specified coordinate.
	// Returns the number of Nodes that are connected to the source Node, which contain the same type
	// of Token as the source. Throws an exception if the specified coordinate does not reference a
	// Node of this TokenGraph.
	int search(std::pair<int, int>);
	// Returns true iff the Node at the specified coordinate of this TokenGraph has been previously
	// reached from another by means of a call to search(). Throws an exception if the specified
	// coordinate does not reference a Node of this TokenGraph.
	bool isSearched(std::pair<int, int>);
	// Puts the Nodes of this TokenGraph into a native state (i.e. the one that they are in before
	// any search has been performed).
	void cleanupSearch();
	// Returns a mapping from the coordinates of this TokenGraph to the Tokens at those
	// coordinates.
	std::map<std::pair<int, int>, AbstractToken*> tokens();

private:

	class Node {

	public:

		// White: requires processing, Gray: in processing, Black: processed, Red: do not process
		static constexpr int WHITE = 0, GRAY = 1, BLACK = 2, RED = 3;

		AbstractToken* token;
		std::set<Node*>* adjacents;

		// Search Attribute.
		int* color;

		Node();
		Node(const Node&) = delete;
		~Node();
		// Initializes this Node with the specified Token and adjacency set. Should the type of the
		// specified Token match that of the other, the Node that carries it will be reachable from
		// a search initiated from a Node carrying a Token of that type.
		void init(AbstractToken*, AbstractToken*, std::set<Node*>*);

	};

	int* occupied;
	std::map<std::pair<int, int>, Node*>* nodes;
	std::bitset<NUM_TYPES>* types;

	Node* nodeAt(std::pair<int, int>) const;
	std::pair<int, int> validateCoordinate(std::pair<int, int>) const;
	int search(Node*);
	void setupSearchAttributes(AbstractToken*);

};
