#pragma once

#include <vector>

#include "PlayerView.h"

class RosterView {

public:

	RosterView();
	RosterView(const RosterView&) = delete;
	~RosterView();
	void addView(PlayerView*);
	void rotate();
	void showTiles() const;
	void showBuildings() const;
	void showVillage() const;

private:

	int* current;
	std::vector<PlayerView*>* players;

};

