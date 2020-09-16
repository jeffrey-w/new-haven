#pragma once

#include <string>
#include <vector>

#include "AbstractPiece.h"
#include "ResourceToken.h"

using ResourceType = ResourceToken::ResourceType;

// The Piece that occupies HarvestTileDecks and HarvesTileHands.
class HarvestTile : public AbstractPiece {

  public:
    // The number of resources that a HarvestTile holds.
    static constexpr int NUM_RESOURCES = 4;

    static void printTiles(std::ostream&, const std::vector<HarvestTile*>);

    // Constructs a new HarvestTile object.
    HarvestTile();
    // Constructs a new HarvestTile object containing the specified ResourceTokens.
    HarvestTile(ResourceToken*, ResourceToken*, ResourceToken*, ResourceToken*);
    // Constructs a new HarvestTile object with the same resources and configuration as the specified HarvestTile.
    HarvestTile(const HarvestTile&);
    // Destroys this HarvestTile.
    ~HarvestTile();
    // Rotates this HarvestTile 90 degrees counterclockwise. Throws an exception if this tile is already in the
    // process of being tokenized.
    void rotate();
    // Iteratively returns the ResourceTokens that constitute this HarvestTile. Throws an exception if this tile has
    // already been tokenized.
    ResourceToken* tokenize() override;

  private:
    struct Orientation {

        static constexpr int UPPER_LEFT = 0, UPPER_RIGHT = 1, LOWER_LEFT = 2, LOWER_RIGHT = 3;

        int origin;
        int pos;

        Orientation();
        void reorient();
        int current();
    };

    Orientation orientation;
    std::vector<ResourceToken*> resources;
};
