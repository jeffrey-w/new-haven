#pragma once

#include <map>
#include <vector>
#include <array>

class BuildFacility {
public:
	BuildFacility();
	BuildFacility(BuildFacility&);
	~BuildFacility();
	int getScore();
	void markOccupied(int index);
    void markFaceDown(int index);

private:

	std::array<bool,30>* occupied;
    std::array<bool,30>* faceDown;

	int countRows();
	int countCols();

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

