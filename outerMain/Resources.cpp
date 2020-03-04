#include <stdexcept>
#include <iostream>

#include "Resources.h"

using std::vector;

Deck::Deck() {
	pieces = new vector<AbstractPiece*>();
}

Deck::~Deck() {
	delete pieces;
}

bool Deck::isEmpty() const {
	return pieces->empty();
}

void Deck::push(AbstractPiece* piece) {
	if (!piece) {
		throw std::invalid_argument("Cannot add the null piece to a deck.");
	}
	pieces->push_back(piece);
}

AbstractPiece* Deck::pop() {
	if (isEmpty()) {
		throw std::runtime_error("Cannot draw from an empty deck.");
	}
	AbstractPiece* result = pieces->back();
	pieces->pop_back();
	return result;
}

int Deck::getSize() const {
	return pieces->size();
}

std::vector<AbstractPiece*>* Deck::asList() const {
	return pieces;
}

BuildingDeck::BuildingDeck() : Deck() {}

BuildingDeck::BuildingDeck(const BuildingDeck& other) : BuildingDeck() {
	for (auto& piece : *other.asList()) {
		Building* building = static_cast<Building*>(piece);
		push(new Building(*building));
	}
}

void BuildingDeck::add(Building* building) {
	push(building);
}

Building* BuildingDeck::draw() {
	return static_cast<Building*>(pop());
}

HarvestTileDeck::HarvestTileDeck() : Deck() {}

HarvestTileDeck::HarvestTileDeck(const HarvestTileDeck& other) : HarvestTileDeck() {
	for (auto piece : *other.asList()) {
		HarvestTile* tile = static_cast<HarvestTile*>(piece);
		push(new HarvestTile(*tile));
	}
}

void HarvestTileDeck::add(HarvestTile* tile) {
	push(tile);
}

HarvestTile* HarvestTileDeck::draw() {
	return static_cast<HarvestTile*>(pop());
}

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

bool HarvestTileHand::isFull() {
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

bool HarvestTileHand::isEmpty() {
	return !(one || two);
}

HarvestTile* HarvestTileHand::ship() {
	if (!shipment) {
		throw std::runtime_error("Shipment tile already played.");
	}
	return shipment;
}

void HarvestTileHand::display() {
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
	ownedBuildings = new vector<Building*>();
}

BuildingHand::BuildingHand(const BuildingHand& other) : BuildingHand() {
	for (auto& building : *other.ownedBuildings) {
		ownedBuildings->push_back(new Building(*building));
	}
}

BuildingHand::~BuildingHand() {
	delete ownedBuildings;
}

void BuildingHand::insert(Building* building) {
	ownedBuildings->push_back(building);
}

Building* BuildingHand::select(int selection) {
	Building* building;
	if (selection <= 0 || selection > ownedBuildings->size()) {
		throw std::runtime_error("Selection not in range.");
	}
	selection--;
	building = ownedBuildings->at(selection);
	return building;
}

bool BuildingHand::isEmpty() {
	return ownedBuildings->empty();
}

void BuildingHand::display() {
	if (isEmpty()) {
		std::cout << "Building hand is empty!\n";
	}
	for (int i = 0; i < ownedBuildings->size(); i++) {
		if (i == ownedBuildings->size() - 1) {
			ownedBuildings->at(i)->display();
		}
		else {
			ownedBuildings->at(i)->display();
			std::cout << ", ";
		}
	}
	std::cout << "\n";
}