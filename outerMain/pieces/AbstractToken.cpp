#include <stdexcept>
#include <string>
#include <typeinfo>

#include "../util/Debug.h"
#include "AbstractToken.h"

bool AbstractToken::areSameType(AbstractToken* a, AbstractToken* b) {
	if (!a) {
		return !b;
	}
	// RTTI used for safety (is probably not necessary).
	return b && typeid(a) == typeid(b) && a->getType() == b->getType();
}

int AbstractToken::validateType(int type) {
	if (type < 0 || type > NUM_TYPES - 1) {
		throw std::invalid_argument("Type must be between 0 and "
			+ std::to_string(NUM_TYPES - 1) + ".");
	}
	return type;
}
