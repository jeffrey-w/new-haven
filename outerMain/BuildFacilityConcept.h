#pragma once

// Records the number of colonists attracted to a Player's village.
class VillageBuildingScoringFacility {

public:

	// Constructs a new VillageBuildingScoringFacility object.
	VillageBuildingScoringFacility();
	// Constructs a new VillageBuildingScoringFacility obeject with the same score as the specified
	// VillageBuildingScoringFacility.
	VillageBuildingScoringFacility(const VillageBuildingScoringFacility&);
	// Destrorys this VillageBuildingScoringFacility
	~VillageBuildingScoringFacility();
	// Returns the score recorded by this VillageBuildingScoreFacility.
	int getScore() const;
	//Increments the score recorded by this VillageBuildingScoreFacility by the specified amount.
	void incrementBy(int);

private:

	int* score;

};

