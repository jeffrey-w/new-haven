#pragma once

// The base class from which all Tokens (i.e. occupants of TokenGraphs) shall be derived.
class AbstractToken {

public:

	// Returns true iff the specified Tokens have the same type.
	static bool areSameType(AbstractToken*, AbstractToken*);

	// Constructs a new AbstractToken object.
	AbstractToken();
	// Constructs a new AbstractToken object with the same placement status as the specified Token.
	AbstractToken(AbstractToken&);
	// Destroys this AbstractToken.
	~AbstractToken();
	// Returns true iff this Token occupies a TokenGraph.
	bool isPlaced() const;
	// Returns the type of this Token.
	virtual int getType() const = 0;
	// Sets the placement status of this Token to placed.
	void place();
	// Writees this Token to the standard output stream.
	virtual void display() const = 0;

private:

	bool* placed;

};

