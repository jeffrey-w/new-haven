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
