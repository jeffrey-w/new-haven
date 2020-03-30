#include <iostream>

#include "maps/TokenGraph.h"
#include "maps/VGMap.h"
#include "Resources.h"
#include "util/Debug.h"

using std::vector;
using ResourceType = ResourceToken::ResourceType;

HarvestTileHand::HarvestTileHand() {
	one = nullptr;
	two = nullptr;
	shipment = nullptr;
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

void HarvestTileHand::insert(HarvestTile* tile, bool isShipment) {
	if (isShipment) {
		if (shipment) {
			throw std::runtime_error("This hand already has a shipment tile");
		}
		shipment = tile;
	}
	else {
		if (isFull()) {
			throw std::runtime_error("This hand is full.");
		}
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
	stream << "1\t\t2\t\tShipment\n";
	HarvestTile::printHand(stream, *hand.one, *hand.two);
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
	for (auto& building : *owned) {
		delete building;
	}
	delete owned;
}

void BuildingHand::insert(Building* building) {
	owned->push_back(building);
}

Building* BuildingHand::select(int selection) {
	int index = validateSelection(selection);
	Building* building = (*owned)[index];
	owned->erase(owned->begin() + index);
	return building;
}

int BuildingHand::typeOf(int selection) const {
	return (*owned)[validateSelection(selection)]->getType();
}

int BuildingHand::validateSelection(int selection) const {
	if (selection < 1 || selection > owned->size()) {
		throw std::out_of_range("Selection not in range.");
	}
	return selection;
}

int BuildingHand::worth() const {
	int worth = 0;
	for (auto& building : *owned) {
		worth += building->getValue();
	}
	return worth;
}


void BuildingHand::display() const {
	std::cout << *this;
}


std::ostream& operator<<(std::ostream& stream, const BuildingHand& hand) {
	for (int i = 0; i < hand.owned->size(); i++) {
		stream << i + 1 << '\t';
	}
	stream << '\n';
	for (int i = 0; i < hand.owned->size(); i++) {
		if ((*hand.owned)[i]) {
			stream << *(*hand.owned)[i] << '\t';
		}
		else {
			stream << "-\t";
		}
	}
	return std::cout << '\n';
}

BuildingPool::BuildingPool() {
	pool = new vector<Building*>();
	for (int i = 0; i < POOL_SIZE; i++) {
		pool->push_back(nullptr);
	}
}

BuildingPool::BuildingPool(const BuildingPool& other) {
	pool = new vector<Building*>();
	for (auto& building : *other.pool) {
		pool->push_back(new Building(*building));
	}
}

BuildingPool::~BuildingPool() {
	for (auto& building : *pool) {
		delete building;
	}
	delete pool;
}

size_t BuildingPool::getSize() const {
	return pool->size();
}

void BuildingPool::replenish(Deck<Building*>* deck) {
	for (int i = 0; i < POOL_SIZE; i++) {
		if (deck->isEmpty()) {
			break;
		}
		if (!((*pool)[i])) {
			(*pool)[i] = deck->draw();
		}
	}
}

Building* BuildingPool::remove(int selection) {
	Building* result = nullptr;
	if (selection < 1 || selection > POOL_SIZE) {
		throw std::out_of_range("Pool only has five buildings.");
	}
	if(!(result = (*pool)[--selection])){
		throw std::invalid_argument("Building unavailable.");
	}
	(*pool)[selection] = nullptr;
	return result;
}

void BuildingPool::display() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& stream, const BuildingPool& buildings) {
	for (int i = 0; i < BuildingPool::POOL_SIZE; i++) {
		stream << i + 1 << '\t';
	}
	stream << '\n';
	for (auto& building : *buildings.pool) {
		if (building) {
			stream << *building << '\t';
		}
		else {
			stream << "-\t";
		}
	}
	return stream << '\n';
}

Deck<HarvestTile*>* harvestTileDeck() {
	int numTypes = TokenGraph::NUM_TYPES;
	Deck<HarvestTile*>* tiles = new Deck<HarvestTile*>();
	for (int i = 0; i < numTypes; i++) {
		for (int j = 0; j < numTypes; j++) {
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
	for (int i = 0; i < numTypes; i++) {
		for (int j = 0; j < numTypes; j++) {
			for (int k = 0; k < numTypes; k++) {
				if (!(i == j || i == k || j == k)) {
					// For each resource type i, each type j, and each type k, add a new tile
					// with two i (on the first column), one j, and one k.
					tiles->add(new HarvestTile(
						new ResourceToken(static_cast<ResourceType>(i)),
						new ResourceToken(static_cast<ResourceType>(j)),
						new ResourceToken(static_cast<ResourceType>(i)),
						new ResourceToken(static_cast<ResourceType>(k))
					));
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
				}
			}
		}
	}
	return tiles;
}

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
