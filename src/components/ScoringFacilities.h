#pragma once

#include <map>
#include <string>

#include "../observers/Observable.h"

// Records the number of resources available to Players.
class GatherFacility : public Observable {
  public:
    // Constructs a new GatherFacility object.
    GatherFacility();
    // Constructs a new GatherFacility object initialized to the same state as the specified
    // GatherFacility.
    GatherFacility(const GatherFacility&);
    // Destroys this GatherFacility.
    ~GatherFacility();
    // Returns the amount of the sepcified resource type that has been recorded on this
    // GatherFacility. Throws an exception if the specified type is not between 0 and the number of
    // resource types.
    int countOf(int) const;
    // Adjusts the amount of the specified resource type recorded on this GatherFacility by the
    // specified amount. Throws an exception if the specified type is not between 0 and the number
    // of resource types.
    void incrementBy(int, int);
    // Resets the tallies for each resource type recorded on this GatherFacility to zero.
    void reset();

  protected:
    std::string toString() const override;

  private:
    // key: ResourceType value: amount
    std::map<int, int>* count;
};

// Records statistics about a Player's VGMap and BuildingHand.
class BuildFacility {
  public:
    // Constructs a new BuildFacility object with the specified number of unbuilt Buildings
    // recorded onto it. Throws an exception if the specified number of unbuilt buildings is
    // negative.
    BuildFacility(int);
    // Constructs a new BuildFacility in the same state as the sepcified BuildFacility.
    BuildFacility(const BuildFacility&);
    // Destroys this BuildFacility.
    ~BuildFacility();
    // Returns the number of villagers recorded by this BuildFacility.
    int getVillagers() const;
    // Returns the number of built Buildings recorded by this BuildFacility.
    int getBuilt() const;
    // Returns the number of unbuilt Buildings recorded by this BuildFacility.
    int getUnbuilt() const;
    // Sets the nubmer of villagers recorded by this BuildFacility to that specified. Throws an
    // exception if the specified number is negative.
    void setVillagers(int);
    // Sets the nubmer of built Buildings recorded by this BuildFacility to that specified. Throws
    // an exception if the specified number is negative.
    void setBuilt(int);
    // Sets the nubmer of unbuilt Buildings recorded by this BuildFacility to that specified.
    // Throws an exception if the specified number is negative.
    void setUnbuilt(int);

    bool operator<(const BuildFacility&) const;
    bool operator==(const BuildFacility&) const;

  private:
    int* villagers;
    int* built;
    int* unbuilt;

    BuildFacility();
    int validateScore(int);
};
