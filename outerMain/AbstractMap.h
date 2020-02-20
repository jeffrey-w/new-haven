#pragma once

#include "ScoringFacilities.h"
#include "TokenGraph.h"

class AbstractMap {

protected:

	AbstractMap();
	AbstractMap(AbstractMap&) = delete; // Supress copy constructor.
	~AbstractMap();
	void build(int, int);
	int typeAt(std::pair<int, int>);
	void setSpace(AbstractToken*, std::pair<int, int>);
	void calculate(ScoringFacility*, std::pair<int, int>);

private:

	TokenGraph* graph;

};

