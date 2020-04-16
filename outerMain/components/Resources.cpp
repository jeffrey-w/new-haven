#include <sstream>

#include "../maps/TokenGraph.h"
#include "../maps/VGMap.h"
#include "../util/Debug.h"
#include "Resources.h"

using std::string;
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
	shipment = other.shipment ? new HarvestTile(*other.shipment) : nullptr;
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
	if (one) {
		two = tile;
	}
	else {
		one = tile;
	}
	notify();
}

bool HarvestTileHand::isFull() const {
	return one && two;
}

HarvestTile* HarvestTileHand::select(int selection) {
	return validateSelection(selection, true);
}

void HarvestTileHand::rotate(int selection) {
	validateSelection(selection, false)->rotate();
	notify();
}

HarvestTile* HarvestTileHand::validateSelection(int selection, bool remove) {
	HarvestTile* tile;
	switch (selection) {
	case 1:
		if (one) {
			tile = one;
			if (remove) {
				one = nullptr;
			}
			break;
		}
		else {
			throw std::runtime_error("Tile unavailable.");
		}
	case 2:
		if (two) {
			tile = two;
			if (remove) {
				two = nullptr;
			}
			break;
		}
		else {
			throw std::runtime_error("Tile unavailable.");
		}
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
	HarvestTile* tile = shipment;
	shipment = nullptr;
	notify();
	return tile;
}

void HarvestTileHand::receive(HarvestTile* tile) {
	if (shipment) {
		throw std::runtime_error("Shipment already exists.");
	}
	shipment = tile;
	notify();
}

string* HarvestTileHand::toString() const {
	std::ostringstream stream;
	stream << "1\t\t2\t\t";
	if (shipment) {
		stream << "3 - Shipment";
	}
	stream << '\n';
	HarvestTile::printHand(stream, *one, *two, shipment);
	return new string(stream.str());
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

size_t BuildingHand::getSize() const {
	return owned->size();
}

void BuildingHand::insert(Building* building) {
	owned->push_back(building);
	notify();
}

Building* BuildingHand::select(int selection) {
	int index = validateSelection(selection);
	Building* building = (*owned)[index];
	owned->erase(owned->begin() + index);
	notify();
	return building;
}

int BuildingHand::typeOf(int selection) const {
	return (*owned)[validateSelection(selection)]->getType();
}

int BuildingHand::validateSelection(int selection) const {
	if (selection < 1 || selection > owned->size()) {
		throw std::out_of_range("Selection not in range.");
	}
	return --selection;
}

string* BuildingHand::toString() const {
	std::ostringstream stream;
	for (int i = 0; i < owned->size(); i++) {
		stream << i + 1 << '\t';
	}
	stream << '\n';
	for (int i = 0; i < owned->size(); i++) {
		if ((*owned)[i]) {
			stream << *(*owned)[i] << '\t';
		}
		else {
			stream << "-\t";
		}
	}
	stream << '\n';
	return new string(stream.str());
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
	notify();
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
	notify();
	return result;
}

string* BuildingPool::toString() const {
	std::ostringstream stream;
	for (int i = 0; i < POOL_SIZE; i++) {
		stream << i + 1 << '\t';
	}
	stream << '\n';
	for (auto& building : *pool) {
		if (building) {
			stream << *building << '\t';
		}
		else {
			stream << "-\t";
		}
	}
	stream << '\n';
	return new string(stream.str());
}

Deck<HarvestTile*>* harvestTileDeck() {
	int numTypes = AbstractToken::NUM_TYPES;
	Deck<HarvestTile*>* tiles = new Deck<HarvestTile*>();
	for (int i = 0; i < numTypes; i++) {
		for (int j = 0; j < numTypes; j++) {
			if (i != j) {
				// For each resource type i and each type j, add a new tile with three i and one j.
				tiles->add(new HarvestTile(
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(j)),
					new ResourceToken(static_cast<ResourceType>(i))
				));
				// For each resource type i and each type j, add a new tile with two i and two j.
				tiles->add(new HarvestTile(
					new ResourceToken(static_cast<ResourceType>(i)),
					new ResourceToken(static_cast<ResourceType>(j)),
					new ResourceToken(static_cast<ResourceType>(j)),
					new ResourceToken(static_cast<ResourceType>(i))
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
						new ResourceToken(static_cast<ResourceType>(k)),
						new ResourceToken(static_cast<ResourceType>(i))
					));
					if (j < k) {
						// For each resource type i, each type j, and each type k, add a new tile
						// with two i (on the main diagonal), one j, and one k.
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
	}
	tiles->shuffle();
	return tiles;
}

Deck<Building*>* buildingDeck() {
	Deck<Building*>* buildings = new Deck<Building*>();
	for (int i = 0; i < VGMap::HEIGHT; i++) {
		for (int j = 0; j < VGMap::HEIGHT; j++) {
			for (int k = 0; k < AbstractToken::NUM_TYPES; k++) {
				BuildingType type = static_cast<BuildingType>(k);
				buildings->add(new Building(type, i + 1));
			}
		}
	}
	buildings->shuffle();
	return buildings;
}
