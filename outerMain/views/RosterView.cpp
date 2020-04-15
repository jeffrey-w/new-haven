#include "RosterView.h"

using std::vector;

RosterView::RosterView() {
	current = new int(0);
	players = new vector<PlayerView*>();
}

RosterView::~RosterView() {
	delete current;
	delete players;
}

void RosterView::addView(PlayerView* view) {
	players->push_back(view);
}

void RosterView::rotate() {
	*current = ++(*current) % players->size();
}

void RosterView::showTiles() const {
	(*players)[*current]->showTiles();
}

void RosterView::showBuildings() const {
	(*players)[*current]->showBuildings();
}

void RosterView::showVillage() const {
	(*players)[*current]->showVillage();
}
