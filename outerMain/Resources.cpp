#include <iostream>

#include "maps/TokenGraph.h"
#include "maps/VGMap.h"
#include "Resources.h"

using std::vector;
using ResourceType = ResourceToken::ResourceType;

Deck<Building*>* buildingDeck() {
	Deck<Building*>* buildings = new Deck<Building*>();
	for (int i = 0; i < VGMap::HEIGHT; i++) {
		for (int j = 0; j < VGMap::HEIGHT; j++) {
			for (int k = 0; k < TokenGraph::NUM_TYPES; k++) {
				BuildingType type = static_cast<BuildingType>(k);
				buildings->add(new Building(type, i + 1));
			}
		}
	}
	return buildings;
}

Deck<HarvestTile*>* harvestTileDeck() {
	Deck<HarvestTile*>* tiles = new Deck<HarvestTile*>();
	for (int i = 0; i < TokenGraph::NUM_TYPES; i++) {
		for (int j = 0; j < TokenGraph::NUM_TYPES; j++) {
			if (i != j) {
				// For each resource type i and each type j, add a new tile with three i and one j.
				tiles->add(new HarvestTile(
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(j))
				));
				// For each resource type i and each type j, add a new tile with two i and two j.
				tiles->add(new HarvestTile(
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(j)),
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(j))
				));
			}
		}
	}
	for (int i = 0; i < TokenGraph::NUM_TYPES; i++) {
		for (int j = 0; j < TokenGraph::NUM_TYPES; j++) {
			for (int k = 0; k < TokenGraph::NUM_TYPES; k++) {
				if (!(i == j || i == k || j == k)) {
					if (j < k) {
						// For each resource type i, each type j, and each type k, add a new tile
						// with two i (on the main diagonal), one j, and one k.
						tiles->add(new HarvestTile(
							new ResourceToken(static_cast<ResourceType>(i)),
							new ResourceToken(static_cast<ResourceType>(j)),
							new ResourceToken(static_cast<ResourceType>(k)),
							new ResourceToken(static_cast<ResourceType>(i))
						));
					}
					// For each resource type i, each type j, and each type k, add a new tile
					// with two i (on the first column), one j, and one k.
					tiles->add(new HarvestTile(
						new ResourceToken(static_cast<ResourceType>(i)),
						new ResourceToken(static_cast<ResourceType>(j)),
						new ResourceToken(static_cast<ResourceType>(i)),
						new ResourceToken(static_cast<ResourceType>(k))
					));
				}
			}
		}
	}
	return tiles;
}

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
