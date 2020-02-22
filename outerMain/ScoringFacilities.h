#pragma once

#include <map>

class BuildFacility {
	
	// TODO

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

