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
	try {
		file.open(path);
		read(&file);
	} catch (ifstream::failure& e) {
		std::cerr << "Caught ifstream::failure: ";
		std::cerr << e.what() << std::endl;
		std::cerr << "Error code: " << e.code() << std::endl;
		nodes->clear();
	}
	file.close();
}

GBMapLoader::~GBMapLoader() {
	delete nodes;
	nodes = nullptr;
}

GBMap* GBMapLoader::load() {
	GBMap* map = new GBMap(*numPlayers);
	for (auto node : *nodes) {
		map->setSquare(node.first, node.second);
	}
	// TODO validate if required, but this is guaranteed to be "valid"
	return map;
}

void GBMapLoader::read(ifstream* file) {
	// TODO
}
