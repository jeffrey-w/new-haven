#pragma once

class ScoringFacility {

public:

	virtual void incrementBy(int, int) = 0;

};

class BuildFacility : public ScoringFacility {

};

class GatherFacility : public ScoringFacility {

public:

	bool isCalculated(int);
	void setCalculated(int);

};

