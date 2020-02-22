#include "Building.h"

BuildingToken* Building::next() {
	if (*spent) {
		throw new std::exception();
	}
	*spent = true;
	return token;
}
