#pragma once

#include <map>
#include <string>

#include "../observers/Observable.h"

// Records the number of resources available to Players.
class ResourceTracker : public Observable {

  public:
    // Constructs a new ResourceTracker object.
    ResourceTracker();
    // Constructs a new ResourceTracker object initialized to the same state as the specified ResourceTracker.
    ResourceTracker(const ResourceTracker&);
    // Returns the amount of the sepcified resource type that has been recorded on this ResourceTracker. Throws an
    // exception if the specified type is not between zero and the number of resource types.
    int countOf(int) const;
    // Resets the tallies for each resource type recorded on this ResourceTracker to zero.
    void reset();
    // Decrements this ResourceTracker's count of the specified type by the specified cost. Throws an exception if the
    // specified type is out of this ResourceTracker's bounds, or if the resources available are insufficiet to cover
    // the specified cost.
    void use(int, int);
    // Increments this ResourceTracker's count of the specified type by the specified amount. Throws an exception if
    // the specified type is out of this ResourceTracker's bounds, or if the specified amount is negative.
    void save(int, int);

  protected:
    std::string toString() const override;

  private:
    // key: ResourceType value: amount
    std::map<int, int> count;
};
