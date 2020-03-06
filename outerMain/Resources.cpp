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
	one = new HarvestTile(*other.one);
	two = new HarvestTile(*other.two);
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
	std::cout << "[1]st:\n";
	if (one) {
		one->display();
	}
	else {
		std::cout << "None\n";
	}
	std::cout << "[2]nd:\n";
	if (two) {
		two->display();
	}
	else {
		std::cout << "None\n";
	}
	std::cout << "Shipment:\n";
	if (shipment) {
		shipment->display();
	}
	else {
		std::cout << "None\n";
	}
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
	if (selection <= 0 || selection > owned->size()) {
		throw std::runtime_error("Selection not in range.");
	}
	selection--;
	building = owned->at(selection);
	return building;
}


void BuildingHand::display() const {
	if (isEmpty()) {
		std::cout << "Building hand is empty!\n";
	}
	for (int i = 0; i < owned->size(); i++) {
		if (i == owned->size() - 1) {
			owned->at(i)->display();
		}
		else {
			owned->at(i)->display();
			std::cout << ", ";
		}
	}
	std::cout << "\n";
}

bool BuildingHand::isEmpty() const {
	return owned->empty();
}