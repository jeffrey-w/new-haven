#include <iostream>

#include "Resources.h"

using std::vector;

HarvestTileHand::HarvestTileHand() : HarvestTileHand(new HarvestTile()) {}

HarvestTileHand::HarvestTileHand(HarvestTile* shipment) {
	one = nullptr;
	two = nullptr;
	this->shipment = shipment;
}

HarvestTileHand::HarvestTileHand(const HarvestTileHand& other) {
	one = other.one ? new HarvestTile(*other.one) : nullptr;
	two = other.two ? new HarvestTile(*other.two) : nullptr;
	shipment = new HarvestTile(*other.shipment);
}

HarvestTileHand::~HarvestTileHand() {
	delete one;
	delete two;
	delete shipment;
}

void HarvestTileHand::insert(HarvestTile* tile) {
	if (isFull()) {
		throw std::runtime_error("This hand is full.");
	}
	else {
		if (one) {
			two = tile;
		}
		else {
			one = tile;
		}
	}
}

bool HarvestTileHand::isFull() const {
	return one && two;
}

HarvestTile* HarvestTileHand::exchange(int selection) {
	HarvestTile* tile;
	if (isEmpty()) {
		throw std::runtime_error("This hand is empty.");
	}
	switch (selection) {
	case 1:
		tile = one;
		one = nullptr;
		break;
	case 2:
		tile = two;
		two = nullptr;
		break;
	default:
		throw std::invalid_argument("Must select [1]st or [2]nd.");
	}
	return tile;
}

bool HarvestTileHand::isEmpty() const {
	return !(one || two);
}

HarvestTile* HarvestTileHand::ship() {
	if (!shipment) {
		throw std::runtime_error("Shipment tile already played.");
	}
	return shipment;
}

void HarvestTileHand::display() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const HarvestTileHand& hand) {
	stream << "1st:\n";
	if (hand.one) {
		stream << hand.one;
	}
	else {
		stream << "None\n";
	}
	stream << "2nd:\n";
	if (hand.two) {
		stream << hand.two;
	}
	else {
		stream << "None\n";
	}
	stream << "Shipment:\n";
	if (hand.shipment) {
		stream << hand.shipment;
	}
	else {
		stream << "None\n";
	}	
	return stream;
}

BuildingHand::BuildingHand() {
	owned = new vector<Building*>();
}

BuildingHand::BuildingHand(const BuildingHand& other) : BuildingHand() {
	for (auto& building : *other.owned) {
		owned->push_back(new Building(*building));
	}
}

BuildingHand::~BuildingHand() {
	delete owned;
}

void BuildingHand::insert(Building* building) {
	owned->push_back(building);
}

Building* BuildingHand::select(int selection) {
	Building* building;
	if (selection < 1 || selection > owned->size()) {
		throw std::out_of_range("Selection not in range.");
	}
	building = owned->at(--selection);
	return building;
}

int BuildingHand::worth() {
	int worth = 0;
	for (auto& building : *owned) {
		worth += building->getValue();
	}
	return worth;
}


void BuildingHand::display() const {
	std::cout << *this;
}

bool BuildingHand::isEmpty() const {
	return owned->empty();
}

std::ostream& operator<<(std::ostream& stream, const BuildingHand& hand) {
	if (hand.isEmpty()) {
		std::cout << "Building hand is empty!\n";
	}
	for (int i = 0; i < hand.owned->size(); i++) {
		stream << (*hand.owned)[i];
		if (i < hand.owned->size() - 1) {
			stream << ',';
		}
	}
	return std::cout << '\n';
}
