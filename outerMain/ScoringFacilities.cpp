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

int GatherFacility::countOf(int type) { // TODO validate type
	return (*count)[type];
}

void GatherFacility::incrementBy(int type, int amount) { // TODO validate type
	int prior = (*count)[type];
	(*count)[type] = prior + amount;
}

int BuildFacility::getScore() { // TODO avoid magic constants
	int score = 0;
	for (int i = 0; i < 6; i++) {
		bool proceed = true;
		for (int j = 0; j < 5; j++) {
			if (!(*occupied)[(i * 6) + j]) {
				break;
			}
			if (j == 4) {
				score++;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; i < 6; j++) {
			if (!(*occupied)[(j * 6) + i]) {
				break;
			}
			if (j == 5) {
				score++;
			}
		}
	}
	return score;
}
