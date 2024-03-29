#pragma once

#include "../components/BuildingHand.h"
#include "../components/BuildingPool.h"
#include "../components/Deck.h"
#include "../components/HarvestTileHand.h"
#include "../components/ResourceTracker.h"
#include "../components/ScoreBoard.h"
#include "../maps/GBMap.h"
#include "../maps/VGMap.h"
#include "../pieces/HarvestTile.h"

// Forward declaration.
class PlayerView;

// The players of New Haven.
class Player {

  public:
    // Constructs a new Player object.
    Player();
    // Constructs a new Player object with the specified shipment tile;
    Player(HarvestTile*);
    // Returns true iff the this Player is able to build on their VGMap with the resources
    // available in the specified Resources.
    bool canPlay(ResourceTracker*) const;
    // Returns the number of villagers this Player has attracted to their VGMap.
    int getVillagers() const;
    // Returns the number of Buildings this Player has built on thier VGMap.
    int getBuilt() const;
    // Returns the number of Buildings in this Player's BuildingHand.
    int getUnbuilt() const;
    // Induces this Player to draw a Building from the specified Deck. Throws an exception if the specified Deck is
    // null or empty.
    void drawBuilding(Deck<Building*>*);
    // Induces this Player to select a Building from the specified BuildingPool. Throws an exception if the specified
    // BuildingPool is null, if the specified selection is out of range, or if it specifies a non-existant building.
    void drawBuilding(BuildingPool*, int);
    // Induces this Player to draw a HarvestTile from the specified Deck. Throws an exception if the specified Deck is
    // null or empty.
    void drawTile(Deck<HarvestTile*>*);
    // Returns the type of the selected Building. Throws an exception if the selected building is not consistent with
    // this Player's hand.
    int buildingType(int) const;
    // Induces this Player to build the selected Building on their VGMap at the specified circle.
    // Throws an exception if any of the following conditions hold:
    // (1) the selected building is not consistent with this Player's hand,
    // (2) the specified circle is not on this Player's VGMap or it is already occupied, or
    // (3) the specified Building is not being placed adjacent to another of the same type.
    void buildVillage(int, std::pair<int, int>);
    // Rotates the selected HarvestTile 90 degrees counterclockwise. Throws an exception if the specified slection is
    // not consistent with this Player's hand.
    void rotateTile(int);
    // Induces this Player to place the selected HarvestTile onto the specified GBMap at the specified square. Throws
    //an exception if the specified tile selection is not consistent with this Player's Hand, if the specified GBMap is
    // null; or if the specified square is not on the GBMap this Player is playing on or it is already occupied.
    void placeTile(int, GBMap*, std::pair<int, int>);
    // Returns this Player's shipment tile. Throws an exception if this Player has already played their shipment tile.
    HarvestTile* reap();
    // Adds the specified HarvestTile to this Player's Hand as its shipment tile. Throws an exception if this Player
    // already has a shipment tile.
    void store(HarvestTile*);

    bool operator<(const Player&) const;
    bool operator==(const Player&) const;

    friend PlayerView* playerView(Player*);

  private:
    HarvestTileHand tiles;
    BuildingHand buildings;
    VGMap village;
    ScoreBoard score;
};
