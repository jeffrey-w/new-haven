#include "RosterView.h"

using std::vector;

RosterView::RosterView() : current(0) {
}

RosterView::~RosterView() {
    for (auto& player : players) {
        delete player;
    }
}

void RosterView::addView(PlayerView* view) {
    if (!view) {
        throw std::invalid_argument("Cannot observe the null subject.");
    }
    players.push_back(view);
}

void RosterView::rotate() {
    current = ++current % players.size();
}

void RosterView::showTiles() const {
    players[current]->showTiles();
}

void RosterView::showBuildings() const {
    players[current]->showBuildings();
}

void RosterView::showVillage() const {
    players[current]->showVillage();
}
