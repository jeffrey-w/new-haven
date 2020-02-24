#include "AbstractPiece.h"

AbstractPiece::AbstractPiece() {
	spent = new bool(false);
}

AbstractPiece::AbstractPiece(const AbstractPiece& other) {
	spent = new bool(*other.spent);
}

AbstractPiece::~AbstractPiece() {
	delete spent;
}

bool AbstractPiece::isSpent() const {
	return *spent;
}

void AbstractPiece::spend() {
	*spent = true;
}
