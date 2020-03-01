#include <stdexcept>

#include "Resources.h"

using std::vector;

Deck::Deck() {
	pieces = new vector<AbstractPiece*>();
}

Deck::~Deck() {
	delete pieces;
}

bool Deck::empty() const {
	return pieces->empty();
}

void Deck::push(AbstractPiece* piece) {
	if (!piece) {
		throw std::invalid_argument("Cannot add the null Piece to a deck.");
	}
	pieces->push_back(piece);
}

AbstractPiece* Deck::pop() {
	if (empty()) {
		throw std::runtime_error("Cannot draw from an empty deck.");
	}
	AbstractPiece* result = pieces->back();
	pieces->pop_back();
	return result;
}

int Deck::getSize() {
	return pieces->size();
}

std::vector<AbstractPiece*>& Deck::asList() const {
	return *pieces;
}

BuildingDeck::BuildingDeck() : Deck() {
	for (int i = 0; i < 6; i++) {
		for (int number = 1; number <= 6; ++number) {
			for (int type = 0; type < 4; ++type) {
				switch (type) {
				case 0: add(new Building(BuildingType::FOREST, number));
					break;
				case 1: add(new Building(BuildingType::MEADOW, number));
					break;
				case 2: add(new Building(BuildingType::QUARRY, number));
					break;
				case 3: add(new Building(BuildingType::WHEATFIELD, number));
					break;
				}
			}
		}
	}
}

BuildingDeck::BuildingDeck(const BuildingDeck& other) : BuildingDeck() {
	for (auto& piece : other.asList()) {
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
	for (auto piece : other.asList()) {
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

Hand::Hand() : Hand(new HarvestTile()) {}

Hand::Hand(HarvestTile* shipment) {
	one = nullptr;
	two = nullptr;
	this->shipment = shipment;
}

Hand::Hand(const Hand& other) {
	one = new HarvestTile(*other.one);
	two = new HarvestTile(*other.two);
	shipment = new HarvestTile(*other.shipment);
}

Hand::~Hand() {
	delete one;
	delete two;
	delete shipment;
}

void Hand::insert(HarvestTile* tile) {
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


bool Hand::isFull() {
	return one && two;
}

HarvestTile* Hand::exchange(int selection) {
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
		throw std::runtime_error("Must select [1]st or [2]nd.");
	}
	return tile;
}

bool Hand::isEmpty() {
	return !(one || two);
}

HarvestTile* Hand::ship() {
	if (!shipment) {
		throw std::runtime_error("Shipment tile already played.");
	}
	return shipment;
}

