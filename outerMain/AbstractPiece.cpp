#include "AbstractPiece.h"

AbstractPiece::AbstractPiece() {
	spent = new bool(false);
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
