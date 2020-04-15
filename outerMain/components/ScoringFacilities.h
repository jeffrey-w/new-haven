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

	std::string* toString() const override;

private:

	// key: ResourceType value: amount
	std::map<int, int>* count;

};

