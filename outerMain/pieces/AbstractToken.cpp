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

AbstractToken::AbstractToken() {
	placed = new bool(false);
}

AbstractToken::AbstractToken(const AbstractToken& other) {
	placed = new bool(*other.placed);
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
