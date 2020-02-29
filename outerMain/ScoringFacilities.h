#pragma once

#include <map>
#include <vector>
#include <array>

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

private:

	int* score;

};

class GatherFacility {

public:

	GatherFacility();
	GatherFacility(GatherFacility&);
	~GatherFacility();
	int countOf(int type) const;
	void incrementBy(int, int);
	void displayCount() const;

private:

	// key: ResourceType value: amount
	std::map<int, int>* count;

};

