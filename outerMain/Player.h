#pragma once

#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "pieces/Building.h"
#include "pieces/HarvestTile.h"
#include "Resources.h"
#include "ScoringFacilities.h"



class Player {

public:

    // Constructs a new Player object.
    Player();
    // Constructs a new Player object with the same attributes as the specified Player.
    Player(const Player&);
    // Destroys this Player.
    ~Player();
    // Returns this Player's village board.
    VGMap* getVillageBoard();
    // Induces this Player to draw a Building from the specified Deck. Throws an exception if the
    // specified Deck is empty.
    Building* drawBuilding(BuildingDeck*);
    // Induces this Player to draw a HarvestTile from the specified Deck. Throws an exception if
    // the specified Deck is empty.
    void drawHarvestTile(HarvestTileDeck*);
    // Induces this Player to build the specified Building on their VGMap at the specified circle.
    // Throws an exception if any of the following conditions hold:
    // (1) the specified Building is null,
    // (2) the specified circle is not on this Player's VGMap or it is already occupied,
    // (3) the specified Building is not being placed adjacent to another of the same type, or
    // (4) the specified Building is being played face up on a circle that is not the correct value.
    void buildVillage(Building*, std::pair<int, int>);
    // Induces this Player to attempt to place the selected HarvestTile onto the specified GBMap at
    // the specified square. Throws an exception if the specified tile selection is not consistent
    // with this Player's Hand, or if the specified square is not on the GBMap this Player is playing on.
    void placeHarvestTile(int, GBMap*, std::pair<int, int>);
    // Adjusts the specified GatherFacility's count of the specified type according to the
    // specified cost. Throws an exception if the specified type is out of the specified
    // GatherFacility's bounds, or if the resources available to this Player are insufficiet to
    // cover the specified cost.
    void resourceTracker(GatherFacility*, int, int);
    // Counts the resources available to this Player ont he specified GBMap, starting from the
    // specified square, and records the results on the specified GatherFacility. Throws an
    // exception if the specified square is not on the GBMap this Player is playing on.
    void calculateResources(GBMap*, std::pair<int, int>, GatherFacility*);
    // Counts the villagers attracted to this Player's village.
    void calculateScore();

private:
    
    Hand* hand;
    VGMap* villageBoard;
    BuildFacility* buildFacility;

};


