#include <typeinfo>

#include "AbstractToken.h"

bool AbstractToken::areSameType(AbstractToken* a, AbstractToken* b) {
	if (!a) {
		return !b;
	}
	return b && typeid(a) == typeid(b) && a->getType() == b->getType(); // RTTI used for safety (is probably not necessary).
}

AbstractToken::AbstractToken() {
	placed = new bool(false);
}

AbstractToken::~AbstractToken() {
	delete placed;
}

bool AbstractToken::isPlaced() const {
	return *placed;
}

void AbstractToken::place() {
	*placed = true;
}
