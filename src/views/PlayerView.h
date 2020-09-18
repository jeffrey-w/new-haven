#pragma once

#include "../players/Player.h"
#include "View.h"

// Provides Views for a Player's posessions.
class PlayerView {

  public:
    // Constructs a new PlayerView observing the specified Hands and VGMap. Throws an exception if any of the specified Observables are null.
    PlayerView(HarvestTileHand*, BuildingHand*, VGMap*);
    // Suppress copy constructor.
    PlayerView(const PlayerView&) = delete;
    // Destryos this PlayerView.
    ~PlayerView();
    // Displays the HarvestTileHand observed by this PlayerView.
    void showTiles() const;
    // Displays the BuildingHand observed by this PlayerView.
    void showBuildings() const;
    // Displayes the VGMap observed by this PlayerView.
    void showVillage() const;

  private:
    View* tiles;
    View* buildings;
    View* village;
};
