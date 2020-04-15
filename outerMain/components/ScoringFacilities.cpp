#include <sstream>
#include <string>

#include "../maps/VGMap.h"
#include "../pieces/HarvestTile.h"
#include "../util/Debug.h"
#include "ScoringFacilities.h"

using std::map;
using std::string;

GatherFacility::GatherFacility() {
	count = new map<int, int>();
	for (int i = 0; i < AbstractToken::NUM_TYPES; i++) {
		(*count)[i] = 0;
	}
}

GatherFacility::GatherFacility(const GatherFacility& other) {
	count = new map<int, int>(*other.count);
}

GatherFacility::~GatherFacility() {
	delete count;
}

int GatherFacility::countOf(int type) const {
	return (*count)[AbstractToken::validateType(type)];
}

void GatherFacility::incrementBy(int type, int amount) {
	(*count)[AbstractToken::validateType(type)] += amount;
	notify();
}

void GatherFacility::reset() {
	for (auto& entry : *count) {
		entry.second = 0;
	}
	notify();
}

string* GatherFacility::toString() const {
	std::ostringstream stream;
	for (auto& entry : *count) {
		int amount = entry.second;
		switch (entry.first) {
		case 0:
			stream << "Sheep: ";
			break;
		case 1:
			stream << "Stone: ";
			break;
		case 2:
			stream << "Timber: ";
			break;
		case 3:
			stream << "Wheat: ";
			break;
		}
		stream << std::to_string(entry.second) + " ";
	}
	stream << '\n';
	return new string(stream.str());
}
