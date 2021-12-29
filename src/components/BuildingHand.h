#pragma once

#include <cstddef>
#include <vector>

#include "../pieces/Building.h"
#include "../observers/Observable.h"

// The collection of Buildings owned by a Player.
class BuildingHand : public Observable {

  public:
    // Constructs a new BuildingHand object.
    BuildingHand() = default;
    // Constructs a new BuildingHand object with the same contents as the specified BuildingHand.
    BuildingHand(const BuildingHand&);
    // Destroys this BuildingHand.
    ~BuildingHand();
    // Returns the number of Buildings in this BuildingHand.
    size_t getSize() const;
    // Adds the specified Building to this BuildingHand.
    void insert(Building*);
    // Returns the Building selected by a Player. Throws an exception if the specified selection
    // does not exist.
    Building* select(int);
    // Returns the type of the selected Building. Throws an exception if the specified selection
    // does not exist.
    int typeOf(int) const;

  protected:
    std::string toString() const override;

  private:
    std::vector<Building*> buildings;

    int validateSelection(int) const;
};