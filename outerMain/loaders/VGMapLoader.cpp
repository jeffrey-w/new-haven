#include <string>

#include "../util/Debug.h"
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
	Building* building = nullptr;
	VGMap* map = new VGMap();
	while (scanner->hasNext()) {
		try {
			building = nextBuilding();
			pair<int, int> circle = nextCircle();
			map->setCircle(building, circle);
			if (scanner->hasNext()) {
				scanner->consume('\n', errorMessage("Expect a new line"));
			}
		} catch (const std::exception& e) {
			delete building;
			delete map;
			throw e;
		}
	}
	return map;
}

Building* VGMapLoader::nextBuilding() {
	bool faceup;
	int value;
	BuildingType type;
	Building* building = nullptr;
	try {
		scanner->consume('<', errorMessage("Expect a '<'"));
		type = static_cast<BuildingType>(scanner->nextInt());
		scanner->consume('>', errorMessage("Expect a '>'"));
		scanner->consume('<', errorMessage("Expect a '<'"));
		value = scanner->nextInt();
		scanner->consume('>', errorMessage("Expect a '>'"));
		scanner->consume('<', errorMessage("Expect a '<'"));
		faceup = scanner->nextBool();
		scanner->consume('>', errorMessage("Expect a '>'"));
		building = new Building(type, value);
		if (faceup) {
			building->flip();
		}
	} catch (const std::exception& e) {
		delete building;
		throw e;
	}
	return building;
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
		+ std::to_string(scanner->column()) + ".";
}
