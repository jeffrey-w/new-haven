#include "GBMapLoader.h"

using std::pair;
using std::string;

GBMapLoader::GBMapLoader(string path) {
	scanner = new Scanner(path);
}

GBMapLoader::~GBMapLoader() {
	delete scanner;
}

GBMap* GBMapLoader::load() { // TODO catch exceptions
	GBMap* map = new GBMap(getNumPlayers());
	while (scanner->hasNext()) {
		scanner->consume('\n', "Expect a new line.");
		HarvestTile* tile = nextTile();
		pair<int, int> square = nextSquare();
		map->setSquare(tile, square);
	}
	return map;
}

int GBMapLoader::getNumPlayers() {
	int numPlayers;
	scanner->consume('<', "Expect a '<'.");
	numPlayers = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	return numPlayers;
}

HarvestTile* GBMapLoader::nextTile() {
	HarvestTile* tile = new HarvestTile();
	tile->resources->clear(); // TODO this is sloppy
	scanner->consume('<', "Expect a '<'.");
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
		tile->resources->push_back(nextToken());
		if (i != HarvestTile::NUM_RESOURCES - 1) {
			scanner->consume(',', "Expect a ','.");
		}
		else {
			scanner->consume('>', "Expect a '>'.");
		}
	}
	scanner->consume('<', "Expect a '<'.");
	*tile->current = scanner->nextInt(); // TODO need to validate this
	scanner->consume('>', "Expect a '>'.");
	return tile;
}

ResourceToken* GBMapLoader::nextToken() {
	return new ResourceToken(AS_TYPE(scanner->nextInt(), ResourceToken::ResourceType));
}

pair<int, int> GBMapLoader::nextSquare() {
	int one, two;
	scanner->consume('<', "Expect a '<'.");
	one = scanner->nextInt();
	scanner->consume(',', "Expect a ','.");
	two = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	return pair<int, int>(one, two);
}
