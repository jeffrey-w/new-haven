#include "BuildFacilityConcept.h"

VillageBuildingScoringFacility::VillageBuildingScoringFacility() {
	score = new int(0);
}

VillageBuildingScoringFacility::VillageBuildingScoringFacility(const VillageBuildingScoringFacility& other) {
	score = new int(*other.score);
}

VillageBuildingScoringFacility::~VillageBuildingScoringFacility() {
	delete score;
}

int VillageBuildingScoringFacility::getScore() const {
	return *score;
}

void VillageBuildingScoringFacility::incrementBy(int amount) {
	*score += amount;
}
