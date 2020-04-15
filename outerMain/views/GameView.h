#pragma once

#include "RosterView.h"
#include "View.h"

class GameView {

public:

	void showBoard() const;
	void showResources() const;
	void showPool() const;
	void showTiles() const;
	void showBuildings() const;
	void showVillage() const;

private:

	View* board;
	View* resources;
	View* pool;
	RosterView* players;

};

