#include <iostream>
#include <string>

#include "HarvestTile.h"
#include "ScoringFacilities.h"
#include "VGMap.h"

using std::map;
using std::vector;

BuildFacility::BuildFacility() {
	occupied = new std::array<bool,30>();
	faceDown = new std::array<bool,30>();
}

BuildFacility::BuildFacility(BuildFacility& other) {
	occupied = new std::array<bool,30>(*other.occupied);
	faceDown = new std::array<bool,30>(*other.faceDown);
}

BuildFacility::~BuildFacility() {
	delete occupied;
	delete faceDown;
}

int BuildFacility::getScore() {
	return countRows() + countCols();
}

int BuildFacility::countRows() {
	int score = 0;
	bool emptyExists;
	bool faceDownExists;
	for (uint8_t row = 0; row < VGMap::HEIGHT; row++) {
        emptyExists=false;
        faceDownExists=false;
		for (uint8_t col = 0; col < VGMap::WIDTH; col++) {
			if (!(*occupied)[(row * VGMap::WIDTH) + col]) {
			    emptyExists=true;
				break;
			}
            if ((*faceDown)[(row * VGMap::WIDTH) + col]) {
                faceDownExists=true;
			}
		}
		if(emptyExists){continue;}
		score+=(faceDownExists)? VGMap::HEIGHT - row : 2*(VGMap::HEIGHT - row);
	}
	return score;
}

int BuildFacility::countCols() { // TODO avoid magic constants
	int score = 0;
	bool emptyExists;
	bool faceDownExists;
	for (uint8_t col = 0; col < VGMap::WIDTH; col++) {
	    emptyExists=false;
	    faceDownExists=false;
		for (uint8_t row = 0; row < VGMap::HEIGHT; row++) {
			if (!(*occupied)[(row * VGMap::WIDTH) + col]) {
			    emptyExists=true;
				break;
			}
			if((*faceDown)[(row * VGMap::WIDTH)+col]){
			    faceDownExists=true;
			}
		}
		if(emptyExists){ continue;}
        switch(col){
            case 0:
            case 4:
                score+=(faceDownExists)? 5 : 10;
                break;
            case 1:
            case 3:
                score+=(faceDownExists)? 4 : 8;
                break;
            case 2:
                score+=(faceDownExists)? 3 : 6;
        }
	}
	return score;
}

void BuildFacility::markOccupied(int index) { // TODO validate index
	(*occupied)[index] = true;
}

void BuildFacility::markFaceDown(int index) {//TODO validate index
    (*faceDown)[index] = true;
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
