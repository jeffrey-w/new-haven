#pragma once

#include "AbstractToken.h"

// The token type that inhabits spaces on a VGMap.
class BuildingToken : public AbstractToken {

public:

	// The types a BuildingToken may have. (Corresponding ResourceTypes has corresponding
	// ordinals.)
	enum class BuildingType {
		MEADOW,
		QUARRY,
		FOREST,
		WHEATFIELD
	};
	
	// Constructs a new BuildingToken object with a random type.
	BuildingToken();
	// Constructs a new BuildingToken object with the specified type and value. Throws an exception
	// if the specified value is not between one and the height of a VGMap.
	BuildingToken(BuildingType, int);
	// Constructs a new BuildingToken object witht the same type and value as the specified BuildingToken.
	BuildingToken(const BuildingToken&);
	// Destroys this BuildingToken.
	~BuildingToken();
	// Returns true iff this BuildingToken is face up.
	bool isFaceUp() const;
	// Returns the type of this BuildingToken.
	int getType() const;
	// Returns the value of this BuildingToken.
	int getValue() const;
	// Flips this BuildingToken. If it was previously face up, it becomes face down and vice versa.
	void flip();
	// Writes this BuildingToken to the standard output stream.
	void display() const;

	friend std::ostream& operator<<(std::ostream&, const BuildingToken&);

private:

	BuildingType* type;
	int* value;
	bool* faceUp;

	static BuildingType randomType();
	static int randomValue();
	static int validateValue(int);

};
