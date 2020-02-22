#pragma once

#include "AbstractToken.h"

// Instances of the Resource class inhabit spaces on a GBMap.
class ResourceToken : public AbstractToken {

public:

	// The types a Resource may have.
	enum class ResourceType {
		SHEEP,
		STONE,
		TIMBER,
		WHEAT
	};

	// Constructs a new Resource object with a random type.
	ResourceToken();
	// Constructs a new Resource object with the specified type.
	ResourceToken(ResourceType);
	// Constructs a new Resource object with the same type as the specified Resource.
	ResourceToken(ResourceToken&);
	// Destructs this Resource object.
	~ResourceToken();
	// Returns the type of this Resource.
	int getType() const;
	// Writes this Resource to the standard output stream
	void display() const;

private:
	
	ResourceType* type;

	ResourceToken::ResourceType randomType();

};
