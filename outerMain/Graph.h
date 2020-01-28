#pragma once

#include <vector>

#include "Resource.h"

using std::vector;

struct Node {

	Resource* item;
	Node* next;

};

class Graph {

public:

	Graph();
	Node* addVertex();
	void addEdge(Node* u, Node* v);
	void setResource(Resource* r);
	int search(); // can either be BFS or DFS (BFS seems easier)

private:

	vector<Node*>* vertecies;

};

