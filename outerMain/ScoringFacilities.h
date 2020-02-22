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
	void incrementBy(int type, int amount);

private:

	std::map<int, int>* count;

};

