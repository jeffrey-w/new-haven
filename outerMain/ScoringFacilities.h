#pragma once

#include <map>
#include <vector>

class BuildFacility {

	BuildFacility();
	BuildFacility(BuildFacility&);
	~BuildFacility();
	int getScore();
	void markOccupied(int index);

private:

	std::vector<bool>* occupied;

	int countRows();
	int countCols();

};

class GatherFacility {

public:

	GatherFacility();
	GatherFacility(GatherFacility&);
	~GatherFacility();
	int countOf(int type);
	void incrementBy(int, int);

private:

	std::map<int, int>* count;

};

