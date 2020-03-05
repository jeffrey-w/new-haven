#pragma once

#include "AbstractToken.h"

// The base class from which all Pieces (i.e. occupants of Decks and Maps) shall be derived.
class AbstractPiece {

public:

	// Returns true iff this AbstractPiece has been completely tokenized.
	virtual bool isTokenized() const = 0;
	// Iteratively returns the tokens that constitute this AbstractPiece. Throws an exception if
	// this Piece has already been tokenized.
	virtual AbstractToken* tokenize() = 0;
	// Writes this Piece to the standard output stream.
	virtual void display() const = 0;

};
