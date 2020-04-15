#pragma once

#include "../players/Player.h"
#include "View.h"

class PlayerView {

public:

	PlayerView(HarvestTileHand*, BuildingHand*, VGMap*);
	PlayerView(const PlayerView&) = delete;
	~PlayerView();
	void showTiles() const;
	void showBuildings() const;
	void showVillage() const;

private:

	View* tiles;
	View* buildings;
	View* village;

};

