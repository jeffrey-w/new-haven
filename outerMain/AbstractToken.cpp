#include <typeinfo>

#include "AbstractToken.h"

bool AbstractToken::areSameType(AbstractToken* a, AbstractToken* b) {
	if (!a) { // TODO let nullptr mean true?
		return !b;
	}
	return b && typeid(a) == typeid(b) && a->getType() == b->getType(); // RTTI used for safety (is probably not necessary).
}

AbstractToken::AbstractToken() {
	placed = new bool(false);
}

AbstractToken::AbstractToken(AbstractToken& other) {
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
