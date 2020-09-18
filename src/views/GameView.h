#pragma once

#include "../players/Roster.h"
#include "RosterView.h"
#include "View.h"

// Provides Views for several New Haven objects.
class GameView {

  public:
    // Constructs a new GameView object.
    GameView() = default;
    // Suppress copy constructor.
    GameView(const GameView&) = delete;
    // Destroys this GameView.
    ~GameView();
    // Registers an Observer with the specified Roster. Throws an exception if the specified Roster is null.
    void addStats(Roster*);
    // Registers an Observer with the specified GBMap. Throws an exception if the specified GBMap is null.
    void addBoard(GBMap*);
    // Registers an Observer with the specified GatherFacility. Throws an exception if the specified GatherFacility is null.
    void addResources(GatherFacility*);
    // Registers an Observer with the specified BuildingPool. Throws an exception if the specified BuildingPool is null.
    void addPool(BuildingPool*);
    // Registers Observers with the Players in the specified Roster. Throws an exception if the specified Roster is null.
    void addPlayers(Roster*);
    // Selects the next Player to observe.
    void rotate();
    // Displays statistics for every Player Observed by this GameView with the specified header.
    void showStats(const std::string&) const;
    // Displays the GBMap Observed by this GameView.
    void showBoard() const;
    // Displays the GatherFacility observed by this GameView.
    void showResources() const;
    // Displays the BuildingPool observed by this GameView.
    void showPool() const;
    // Displays the HarvestTileHand of the currently observed Player.
    void showTiles() const;
    // Displays the BuildingHand of the currently observed Player.
    void showBuildings() const;
    // Displays the VGMap of the currently observed Player.
    void showVillage() const;

  private:
    View* stats;
    View* board;
    View* resources;
    View* pool;
    RosterView* players;

    static Observable* validateObservable(Observable*);
};
