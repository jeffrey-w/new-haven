#include <iostream>
#include <string>

#include "maps/VGMap.h"
#include "pieces/HarvestTile.h"
#include "ScoringFacilities.h"
#include "util/Debug.h"

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

void BuildFacility::reset() {
	*score = 0;
}

GatherFacility::GatherFacility() {
	count = new map<int, int>();
	for (int i = 0; i < TokenGraph::NUM_TYPES; i++) {
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
	return (*count)[validateType(type)];
}

void GatherFacility::incrementBy(int type, int amount) {
	(*count)[validateType(type)] += amount;
}


int GatherFacility::validateType(int type) const {
	if (type < 0 || type > TokenGraph::NUM_TYPES - 1) { // TODO refactor this to somewhere else
		throw std::runtime_error("Type must be between 0 and "
			+ std::to_string(TokenGraph::NUM_TYPES - 1) + ".");
	}
	return type;
}

void GatherFacility::reset() {
	for (auto& entry : *count) {
		entry.second = 0;
	}
}

void GatherFacility::display() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const GatherFacility& gather) {
	for (auto& entry : *gather.count) {
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
	return stream << '\n';
}
