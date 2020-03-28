#pragma once

// The base class from which all Tokens (i.e. occupants of TokenGraphs) shall be derived.
class AbstractToken {

public:

	// Returns true iff the specified Tokens have the same type.
	static bool areSameType(AbstractToken*, AbstractToken*);
	
	// Destroys this AbstractToken.
	virtual ~AbstractToken() = default;
	// Returns the type of this Token.
	virtual int getType() const = 0;
	// Writes this Token to the standard output stream.
	virtual void display() const = 0;

};
