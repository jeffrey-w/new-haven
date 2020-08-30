#pragma once

#include <vector>

#include "PlayerView.h"

// A collection of PlayerViews.
class RosterView {

  public:
    // Constructs a new RosterView.
    RosterView();
    // Suppress copy constructor.
    RosterView(const RosterView&) = delete;
    // Destroys this RosterView.
    ~RosterView();
    // Adds the specified PlayerView to this RosterView. Throws an exception if the specified
    // PlayerView is null.
    void addView(PlayerView*);
    // Selects the next Player to observe.
    void rotate();
    // Displays the HarvestTileHand observed by this RosterView.
    void showTiles() const;
    // Displays the BuildingHand observed by this RosterView.
    void showBuildings() const;
    // Displays the VGMap observed by this RosterView.
    void showVillage() const;

  private:
    int* current;
    std::vector<PlayerView*>* players;
};
