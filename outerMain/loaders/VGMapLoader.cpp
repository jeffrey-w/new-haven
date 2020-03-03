#include <string>

#include "VGMapLoader.h"

using std::pair;
using std::string;

VGMapLoader::VGMapLoader(const string& path) {
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
			scanner->consume('\n', errorMessage("Expect a new line"));
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
	scanner->consume('<', errorMessage("Expect a '<'"));
	type = static_cast<BuildingToken::BuildingType>(scanner->nextInt());
	scanner->consume('>', errorMessage("Expect a '>'"));
	scanner->consume('<', errorMessage("Expect a '<'"));
	value = scanner->nextInt();
	scanner->consume('>', errorMessage("Expect a '>'"));
	scanner->consume('<', errorMessage("Expect a '<'"));
	faceup = scanner->nextBool();
	scanner->consume('>', errorMessage("Expect a '>'"));
	token = new BuildingToken(type, value);
	if (faceup) {
		token->flip();
	}
	return token;
}

pair<int, int> VGMapLoader::nextCircle() {
	int one, two;
	scanner->consume('<', errorMessage("Expect a '<'"));
	one = scanner->nextInt();
	scanner->consume(',', errorMessage("Expect a ','"));
	two = scanner->nextInt();
	scanner->consume('>', errorMessage("Expect a '>'"));
	return pair<int, int>(one, two);
}

string VGMapLoader::errorMessage(const string& msg) {
	return msg + " at line " + std::to_string(scanner->line()) + ":"
		+ std::to_string(scanner->column() + 1) + ".";
}
