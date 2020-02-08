#include <fstream>
#include <iostream>

#include "GBMapLoader.h"

using std::ifstream;
using std::map;
using std::pair;
using std::string;
using std::vector;

GBMapLoader::GBMapLoader(string path) {
	ifstream file;
	nodes = new map<pair<int, int>, HarvestTile*>();
	edges = new vector<pair<pair<int, int>, pair<int, int>>>();
	try {
		file.open(path);
		read(&file);
	} catch (ifstream::failure& e) {
		std::cerr << "Caught ifstream::failure: ";
		std::cerr << e.what() << std::endl;
		std::cerr << "Error code: " << e.code() << std::endl;
		nodes->clear();
		edges->clear();
	}
	file.close();
}

GBMapLoader::~GBMapLoader() {
	delete nodes;
	delete edges;
	nodes = nullptr;
	edges = nullptr;
}

GBMap GBMapLoader::load() {
	GBMap map(getNumPlayers());
	for (auto node : *nodes) {
		map.addNode(node.first);
		map.setTile(node.first, node.second);
	}
	for (auto edge : *edges) {
		map.addEdge(edge.first, edge.second);
	}
	map.validate();
	return map;
}

void GBMapLoader::read(ifstream* file) {
	// TODO
}

int GBMapLoader::getNumPlayers() {
	switch (nodes->size()) { // TODO avoid magic constants
	case 25:
		return 2;
	case 35:
		return 3;
	case 49:
		return 4;
	default:
		0;
	}
}
