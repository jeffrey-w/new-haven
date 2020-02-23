#include "HarvestTile.h"
#include "ScoringFacilities.h"
#include "VGMap.h"

using std::map;
using std::vector;

BuildFacility::BuildFacility() {
	occupied = new vector<bool>();
}

BuildFacility::BuildFacility(BuildFacility& other) {
	occupied = new vector<bool>(*other.occupied);
}

BuildFacility::~BuildFacility() {
	delete occupied;
}

int BuildFacility::getScore() {
	return countRows() + countCols();
}

int BuildFacility::countRows() {
	int score = 0;
	for (uint8_t row = 0; row < VGMap::HEIGHT; row++) {
		for (uint8_t col = 0; col < VGMap::WIDTH; col++) {
			if (!(*occupied)[(row * VGMap::HEIGHT) + col]) {
				break;
			}
			if (col == VGMap::WIDTH - 1) {
				score += VGMap::HEIGHT - row;
			}
		}
	}
	return score;
}

int BuildFacility::countCols() { // TODO avoid magic constants
	int score = 0;
	for (uint8_t col = 0; col < VGMap::WIDTH; col++) {
		for (uint8_t row = 0; row < VGMap::HEIGHT; row++) {
			if (!(*occupied)[(row * VGMap::HEIGHT) + col]) {
				break;
			}
			if (row == VGMap::HEIGHT - 1) {
				int subtrahend;
				if (col == 0 || col == 4) {
					subtrahend = 1;
				}
				else if (col == 1 || col == 3) {
					subtrahend = 2;
				}
				else {
					subtrahend = 3;
				}
				score += VGMap::HEIGHT - subtrahend;
			}
		}
	}
	return score;
}

void BuildFacility::markOccupied(int index) { // TODO validate index
	(*occupied)[index] = true;
}

GatherFacility::GatherFacility() {
	count = new map<int, int>();
	for (int i = 0; i < HarvestTile::NUM_RESOURCES; i++) {
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
