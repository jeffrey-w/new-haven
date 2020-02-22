#pragma once

#include "AbstractToken.h"

// The base class from which all Pieces (i.e. occupants of Decks and Maps) shall be derived.
class AbstractPiece {

public:

	// Constructs a new AbstractPiece object.
	AbstractPiece();
	// Constructs a new AbstractPiece object with the same spent status as the specified Piece.
	AbstractPiece(AbstractPiece&);
	// Destroys this AbstractPiece.
	~AbstractPiece();
	// Iteratively returns the tokens that constitute this AbstractPiece. Throws an exception if this Piece is spent.
	virtual AbstractToken* tokenize() = 0;
	// Returns true iff this AbstractPiece has been completely tokenized.
	bool isSpent();
	// Sets the status of this AbstractPiece to spent.
	void spend();
	// Writes this Piece to the standard output stream.
	virtual void display() const = 0;

private:

	bool* spent; // TODO make private

};
