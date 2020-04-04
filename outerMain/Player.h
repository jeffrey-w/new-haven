#pragma once

#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "pieces/Building.h"
#include "pieces/HarvestTile.h"
#include "Resources.h"
#include "ScoringFacilities.h"

// The players of New Haven.
class Player {

public:

    // Constructs a new Player object.
    Player();
    // Constructs a new Player object with the specified shipment tile;
    Player(HarvestTile*);
    // Constructs a new Player object with the same attributes as the specified Player.
    Player(const Player&);
    // Destroys this Player.
    ~Player();
    // TODO
    bool canPlay(GatherFacility*);
    // Induces this Player to draw a Building from the specified Deck. Throws an exception if the
    // specified Deck is null or empty.
    void drawBuilding(Deck<Building*>*);
    // Induces this Player to select a Building from the specified BuildingPool. Throws an
    // exception if the specified BuildingPool is null, if the specified selection is out of range,
    // or if it specifies a non-existant building.
    void drawBuilding(BuildingPool*, int);
    // Induces this Player to draw a HarvestTile from the specified Deck. Throws an exception if
    // the specified Deck is null or empty.
    void drawTile(Deck<HarvestTile*>*);
    // Returns the type of the selected Building. Throws an exception if the selected building is
    // not consistent with this Player's hand.
    int buildingType(int) const;
    // Induces this Player to build the selected Building on their VGMap at the specified circle.
    // Throws an exception if any of the following conditions hold:
    // (1) the selected building is not consistent with this Player's hand,
    // (2) the specified circle is not on this Player's VGMap or it is already occupied,
    // (3) the specified Building is not being placed adjacent to another of the same type, or
    void buildVillage(int, std::pair<int, int>);
    // Adjusts the specified GatherFacility's count of the specified type according to the
    // specified cost. Throws an exception if the specified type is out of the specified
    // GatherFacility's bounds, if the specified GatherFacility is null, or if the resources
    // available to this Player are insufficiet to cover the specified cost.
    void resourceTracker(GatherFacility*, int, int); // TODO this belongs in GatherFacility
    // Counts the villagers attracted to this Player's village.
    void calculateScore();
    // Adds the values of the Buildings in this Player's hand to their score.
    void adjustScore();
    // Rotates the selected HarvestTile 90 degrees counterclockwise. Throws an exception if the
    // specified slection is not consistent with this Player's hand.
    void rotateTile(int);
    // Induces this Player to place the selected HarvestTile onto the specified GBMap at the 
    // specified square. Throws an exception if the specified tile selection is not consistent with
    // this Player's Hand, if the specified GBMap is null; or if the specified square is not on the
    // GBMap this Player is playing on or it is already occupied.
    void placeTile(int, GBMap*, std::pair<int, int>);
    // Returns this Player's shipment tile. Throws an exception if this Player has already played
    // thier shipment tile.
    HarvestTile* reap();
    // Adds the specified HarvestTile to this Player's Hand as its shipment tile. Throws an
    // exception if this Player already has a shipment tile.
    void store(HarvestTile*);
    // Writes this Player's HarvestTileHand to the standard output stream.
    void displayTiles() const;
    // Writes this Player's BuildingHand to the standard output stream.
    void displayBuildings() const;
    // Writes this Player's VGMap to the standard output stream.
    void displayVillage() const;

private:
    
    HarvestTileHand* tiles;
    BuildingHand* buildings;
    VGMap* village;
    BuildFacility* score;


};
