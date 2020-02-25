#pragma once

#include "AbstractToken.h"

// The base class from which all Pieces (i.e. occupants of Decks and Maps) shall be derived.
class AbstractPiece {

public:

	// Returns true iff this AbstractPiece has been completely tokenized.
	virtual bool isSpent() const = 0;
	// Iteratively returns the tokens that constitute this AbstractPiece. Throws an exception if this Piece is spent.
	virtual AbstractToken* tokenize() = 0;

};
