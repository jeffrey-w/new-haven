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
	GBMap* map = new GBMap(scanner->nextInt());
	while (scanner->hasNext()) {
		ResourceToken one = nextToken();
		ResourceToken two = nextToken();
		ResourceToken three = nextToken();
		ResourceToken four = nextToken();
		HarvestTile tile(one, two, three, four);
		map->setSquare(&tile, nextSquare());
	}
	return map;
}

ResourceToken GBMapLoader::nextToken() {
	return ResourceToken(static_cast<ResourceToken::ResourceType>(scanner->nextInt()));
}

pair<int, int> GBMapLoader::nextSquare() {
	return pair<int, int>(scanner->nextInt(), scanner->nextInt());
}
