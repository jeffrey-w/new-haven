#pragma once

#include "AbstractToken.h"

// The base class from which all Pieces (i.e. occupants of Decks and Hands) shall be derived.
class AbstractPiece {

public:

	// Destroys this AbstractPiece.
	virtual ~AbstractPiece() = default;
	// Iteratively returns the tokens that constitute this AbstractPiece.
	virtual AbstractToken* tokenize() = 0;
	// Writes this Piece to the standard output stream.
	virtual void display() const = 0;

};
