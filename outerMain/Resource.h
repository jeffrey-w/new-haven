#pragma once

#include "AbstractToken.h"

// Instances of the Resource class inhabit spaces on a GBMap.
class Resource : public AbstractToken {

public:

	// The types a Resource may have.
	enum class ResourceType {
		SHEEP,
		STONE,
		TIMBER,
		WHEAT
	};

	// Returns true iff the specified resources have the same type, otherwise false.
	static bool equals(Resource*, Resource*);

	// Constructs a new Resource object with a random type.
	Resource();
	// Constructs a new Resource object with the specified type.
	Resource(ResourceType);
	// Constructs a new Resource object with the same type as the specified Resource.
	Resource(Resource&);
	// Destructs this Resource object.
	~Resource();
	// Returns the type of this Resource.
	int getType() const;
	// Writes this Resource to the standard output stream
	void display() const;

private:
	
	ResourceType* type;

	Resource::ResourceType randomType();

};
