#include <string>

#include "../util/Debug.h"
#include "GBMapLoader.h"

using std::pair;
using std::string;

GBMapLoader::GBMapLoader(const string& path) {
	scanner = new Scanner(path);
}

GBMapLoader::~GBMapLoader() {
	delete scanner;
}

GBMap* GBMapLoader::load() {
	HarvestTile* tile = nullptr;
	GBMap* map = new GBMap(getNumPlayers());
	while (scanner->hasNext()) {
		try {
			scanner->consume('\n', errorMessage("Expect a new line"));
			tile = nextTile();
			pair<int, int> square = nextSquare();
			map->setSquare(tile, square);
		} catch (const std::exception& e) {
			delete tile;
			delete map;
			throw e;
		}
	}
	return map;
}

int GBMapLoader::getNumPlayers() {
	int numPlayers;
	scanner->consume('<', errorMessage("Expect a '<'"));
	numPlayers = scanner->nextInt();
	scanner->consume('>', errorMessage("Expect a '>'"));
	return numPlayers;
}

HarvestTile* GBMapLoader::nextTile() {
	HarvestTile* tile = nullptr;
	try {
		scanner->consume('<', errorMessage("Expect a '<'"));
		tile = new HarvestTile(scanner->nextInt());
		scanner->consume('>', errorMessage("Expect a '>'"));
		scanner->consume('<', errorMessage("Expect a '<'"));
		for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
			tile->resources->push_back(nextToken());
			if (i != HarvestTile::NUM_RESOURCES - 1) {
				scanner->consume(',', errorMessage("Expect a ','"));
			}
			else {
				scanner->consume('>', errorMessage("Expect a '>'"));
			}
		}
	} catch (const std::exception& e) {
		delete tile;
		throw e;
	}
	return tile;
}

ResourceToken* GBMapLoader::nextToken() {
	return new ResourceToken(static_cast<ResourceType>(scanner->nextInt()));
}

pair<int, int> GBMapLoader::nextSquare() {
	int one, two;
	scanner->consume('<', errorMessage("Expect a '<'"));
	one = scanner->nextInt();
	scanner->consume(',', errorMessage("Expect a ','"));
	two = scanner->nextInt();
	scanner->consume('>', errorMessage("Expect a '>'"));
	return pair<int, int>(one, two);
}

string GBMapLoader::errorMessage(const string& msg) {
	return msg + " at line " + std::to_string(scanner->line()) + ":"
		+ std::to_string(scanner->column()) + ".";
}
