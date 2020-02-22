#include "ScoringFacilities.h"

using std::map;

GatherFacility::GatherFacility() {
	count = new map<int, int>();
	for (int i = 0; i < 4; i++) { // TODO avoid magic constants
		(*count)[i] = 0;
	}
}

GatherFacility::GatherFacility(GatherFacility& other) {
	count = new map<int, int>(*other.count);
}

GatherFacility::~GatherFacility() {
	delete count;
}

void GatherFacility::incrementBy(int type, int amount) { // TODO validate type
	int prior = (*count)[type];
	(*count)[type] = prior + amount;
}
