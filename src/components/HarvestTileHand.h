#pragma once

#include "../observers/Observable.h"
#include "../pieces/HarvestTile.h"

// The collection of HarvestTiles owned by a Player.
class HarvestTileHand : public Observable {

  public:
    constexpr static int SIZE = 3;

    // Constructs a new HarvestTileHand object.
    HarvestTileHand();
    // Constructs a new HarvestTileHand object with the specified shipment tile.
    HarvestTileHand(HarvestTile*);
    // Constructs a new HarvestTileHand object with the same contents as the specified Hand.
    HarvestTileHand(const HarvestTileHand&);
    // Destroys this HarvestTileHand.
    ~HarvestTileHand();
    // Adds the specified HarvestTile to this HarvestTileHand. Throws an exception if this HarvestTileHand is full.
    void insert(HarvestTile*);
    // Returns the HarvestTile selected by a Player. Throws an exception if the specified selection is not between one
    // and two inclusive, or the specified selection does not exit.
    HarvestTile* select(int);
    // Rotates the selected HarvestTile 90 degrees counterclockwise. Throws an exception if the specified slection is
    // not betwewn one and two inclusive, or the specified seleciton does not exist.
    void rotate(int);
    // Returns this HarvestTileHand's shipment tile. Throws an exception if this Hand does not contain a shipment tile.
    HarvestTile* ship();
    // Adds the specified HarvestTile to this Hand as its shipment tile. Throws an exception if this Hand already has a
    // shipment tile.
    void receive(HarvestTile*);

  protected:
    std::string toString() const override;

  private:
    std::vector<HarvestTile*> tiles;

    bool isEmpty() const;
    HarvestTile* validateSelection(int, bool);
};