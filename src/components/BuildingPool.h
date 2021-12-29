#pragma once

#include <string>

#include "../observers/Observable.h"
#include "../pieces/AbstractPiece.h"
#include "../pieces/Building.h"
#pragma once

#include "Deck.h"

// A common collection of Buildings.
class BuildingPool : public Observable {

    static constexpr int SIZE = 5;

  public:
    // Constructs a new BuildingPool object.
    BuildingPool();
    // Constructs a new BuildingPool object with the same contents as the specified BuildingPool.
    BuildingPool(const BuildingPool&);
    // Destroys this BuildingPool.
    ~BuildingPool();
    // Returns the number of Buildings in this BuildingPool.
    size_t getSize() const;
    // Fills this BuildingPool to capacity with Buildings from the specified Deck.
    void replenish(Deck<Building*>*);
    // Removes the selected Building from this BuildingPool.
    Building* remove(int);

  protected:
    std::string toString() const override;

  private:
    std::vector<Building*> buildings;
};
