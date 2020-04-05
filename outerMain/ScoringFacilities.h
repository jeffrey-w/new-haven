#pragma once

#include <map>

// Records the number of colonists attracted to a Player's village.
class BuildFacility {

public:

	// Constructs a new VillageBuildingScoringFacility object.
	BuildFacility();
	// Constructs a new VillageBuildingScoringFacility obeject with the same score as the specified
	// VillageBuildingScoringFacility.
	BuildFacility(const BuildFacility&);
	// Destrorys this VillageBuildingScoringFacility
	~BuildFacility();
	// Returns the score recorded by this VillageBuildingScoreFacility.
	int getScore() const;
	// Increments the score recorded by this VillageBuildingScoreFacility by the specified amount.
	void incrementBy(int);
	// Resets this BuildFacility to zero.
	void reset();

private:

	int* score;

};

// Records the number of resources available to Players.
class GatherFacility {

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
	// Writes this GatherFacility to the statndard output stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const GatherFacility&);

private:

	// key: ResourceType value: amount
	std::map<int, int>* count;

	int validateType(int) const;

};

