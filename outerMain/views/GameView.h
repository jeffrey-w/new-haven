#pragma once

#include "../players/Roster.h"
#include "RosterView.h"
#include "View.h"

class GameView {

public:

	GameView() = default;
	GameView(const GameView&) = delete;
	~GameView();
	void addStats(Roster*);
	void addBoard(GBMap*);
	void addResources(GatherFacility*);
	void addPool(BuildingPool*);
	void addPlayers(Roster*);
	void rotate();
	void showStats(const std::string&) const;
	void showBoard() const;
	void showResources() const;
	void showPool() const;
	void showTiles() const;
	void showBuildings() const;
	void showVillage() const;

private:

	View* stats;
	View* board;
	View* resources;
	View* pool;
	RosterView* players;

};

