#pragma once

#include "AbstractToken.h"

class AbstractPiece {

public:

	AbstractPiece();
	AbstractPiece(AbstractPiece&);
	~AbstractPiece();
	virtual AbstractToken* next() = 0;
	virtual void display() = 0;

protected:

	bool* spent;

};

