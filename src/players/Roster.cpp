#include <sstream>

#include "Roster.h"

using std::deque;
using std::list;
using std::map;
using std::string;

Roster::Roster() {
    ids = new deque<long>();
    players = new map<long, Player*>();
}

Roster::Roster(const Roster& other) : Roster() {
    for (auto& id : *other.ids) {
        ids->push_back(id);
    }
    for (auto& entry : *other.players) {
        (*players)[entry.first] = new Player(*entry.second);
    }
}

Roster::~Roster() {
    for (auto& entry : *players) {
        delete entry.second;
    }
    delete ids;
    delete players;
}

size_t Roster::getSize() const {
    return players->size();
}

long Roster::nextID() const {
    if (ids->empty()) {
        throw std::runtime_error("Roster is empty.");
    }
    return ids->front();
}

void Roster::add(long id, Player* player) {
    if (id < 1) {
        throw std::invalid_argument("ID must be positive.");
    }
    if (players->count(id)) {
        throw std::invalid_argument("ID already exists.");
    }
    if (!player) {
        throw std::invalid_argument("Cannot add the null player.");
    }
    ids->push_back(id);
    (*players)[id] = player;
}

Player* Roster::peek() {
    return front(false);
}

Player* Roster::next() {
    return front(true);
}

Player* Roster::front(bool rotate) {
    if (ids->empty()) {
        throw std::runtime_error("Roster is empty.");
    }
    long id = ids->front();
    if (rotate) {
        ids->pop_front();
        ids->push_back(id);
    }
    return (*players)[id];
}

void Roster::sort() {
    std::sort(ids->begin(), ids->end());
}

void Roster::deal(Deck<HarvestTile*>* tiles, Deck<Building*>* buildings) {
    if (!(tiles && buildings)) {
        throw std::invalid_argument("Cannot deal from null deck(s).");
    }
    for (int i = 0; i < TILE_HAND_SIZE; i++) {
        for (auto& entry : *players) {
            entry.second->drawTile(tiles);
        }
    }
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        for (auto& entry : *players) {
            entry.second->drawBuilding(buildings);
        }
    }
}

string Roster::toString() const {
    std::ostringstream stream;
    for (auto& entry : invert()) {
        stream << "Player " << entry.second << '\n';
        stream << "villagers: " << entry.first.getVillagers();
        stream << " built: " << entry.first.getBuilt();
        stream << " unbuilt: " << entry.first.getUnbuilt() << '\n';
    }
    stream << '\n';
    return stream.str();
}

std::multimap<const Player, long> Roster::invert() const {
    std::multimap<const Player, long> sorted;
    for (auto& entry : *players) {
        sorted.insert({*entry.second, entry.first});
    }
    return sorted;
}

RosterView* rosterView(Roster* roster) {
    RosterView* view = new RosterView();
    for (auto& entry : *roster->players) {
        view->addView(playerView(entry.second));
    }
    return view;
}
