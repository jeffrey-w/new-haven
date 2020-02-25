#include "VGMapLoader.h"

using std::pair;
using std::string;

VGMapLoader::VGMapLoader(string path) {
	scanner = new Scanner(path);
}

VGMapLoader::~VGMapLoader() {
	delete scanner;
}

VGMap* VGMapLoader::load() {
	VGMap* map = new VGMap();
	while (scanner->hasNext()) {
		Building* building = nextBuilding();
		pair<int, int> circle = nextCircle();
		map->setCircle(building, circle);
		if (scanner->hasNext()) {
			scanner->consume('\n', "Expect a new line.");
		}
	}
	return map;
}

Building* VGMapLoader::nextBuilding() {
	Building* building = new Building();
	building->token = nextToken();
	return building;
}

BuildingToken* VGMapLoader::nextToken() {
	bool faceup;
	int value;
	BuildingToken::BuildingType type;
	BuildingToken* token;
	scanner->consume('<', "Expect a '<'.");
	type = static_cast<BuildingToken::BuildingType>(scanner->nextInt());
	scanner->consume('>', "Expect a '>'.");
	scanner->consume('<', "Expect a '<'.");
	value = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	scanner->consume('<', "Expect a '<'.");
	faceup = scanner->nextBool();
	scanner->consume('>', "Expect a '>'.");
	token = new BuildingToken(type, value);
	if (faceup) {
		token->flip();
	}
	return token;
}

pair<int, int> VGMapLoader::nextCircle() {
	int one, two;
	scanner->consume('<', "Expect a '<'.");
	one = scanner->nextInt();
	scanner->consume(',', "Expect a ','.");
	two = scanner->nextInt();
	scanner->consume('>', "Expect a '>'.");
	return pair<int, int>(one, two);
}
