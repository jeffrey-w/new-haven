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
		map->setSquare(nextTile(), nextSquare());
	}
	return map;
}

int GBMapLoader::getNumPlayers() {
	int numPlayers;
	scanner->consume('<', "Expect a '<'.");
	numPlayers = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	scanner->consume('\n', "Expect a new line.");
}

HarvestTile* GBMapLoader::nextTile() {
	HarvestTile* tile = new HarvestTile();
	scanner->consume('<', "Expect a '<'.");
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
		if (!scanner->hasNext()) {
			throw new std::exception(); // TODO need richer exception type
		}
		tile->resources->push_back(nextToken());
		if (i != HarvestTile::NUM_RESOURCES - 1) {
			scanner->consume(',', "Expect a ','.");
			scanner->consume(' ', "Expect a space.");
		}
		scanner->consume('>', "Expect a '>'.");
		scanner->consume(' ', "Expect a space.");
	}
	return tile;
}

ResourceToken* GBMapLoader::nextToken() {
	return new ResourceToken(static_cast<ResourceToken::ResourceType>(scanner->nextInt()));
}

pair<int, int> GBMapLoader::nextSquare() {
	int one, two;
	scanner->consume(' ', "Expect a '<'.");
	one = scanner->nextInt();
	scanner->consume(',', "Expect a ','.");
	scanner->consume(' ', "Expect a space");
	two = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	scanner->consume('\n', "Expect a new line.");
	return pair<int, int>(one, two);
}
