#include <iostream>
#include <string>

#include "HarvestTile.h"
#include "ScoringFacilities.h"
#include "VGMap.h"

using std::map;

BuildFacility::BuildFacility() {
	score = new int(0);
}

BuildFacility::BuildFacility(const BuildFacility& other) {
	score = new int(*other.score);
}

BuildFacility::~BuildFacility() {
	delete score;
}

int BuildFacility::getScore() const {
	return *score;
}

void BuildFacility::incrementBy(int amount) {
	*score += amount;
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

int GatherFacility::countOf(int type) const { // TODO validate type
	return (*count)[type];
}

void GatherFacility::incrementBy(int type, int amount) { // TODO validate type
	int prior = (*count)[type];
	(*count)[type] = prior + amount;
}

void GatherFacility::displayCount() const {
	for (auto& entry : *count) {
		int amount = entry.second;
		switch (entry.first) {
		case 0:
			std::cout << "Sheep: ";
			break;
		case 1:
			std::cout << "Stone: ";
			break;
		case 2:
			std::cout << "Timber: ";
			break;
		case 3:
			std::cout << "Wheat: ";
			break;
		}
		std::cout << std::to_string(entry.second) + " ";
	}
	std::cout << '\n';
}
