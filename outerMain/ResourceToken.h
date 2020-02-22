#pragma once

#include "AbstractToken.h"

// The token type that inhabits spaces on a GBMap.
class ResourceToken : public AbstractToken {

public:

	// The types a Resource may have. (Corresponding BuildingType have corresponding ordinal.)
	enum class ResourceType {
		SHEEP,
		STONE,
		TIMBER,
		WHEAT
	};

	// Constructs a new ResourceToken object with a random type.
	ResourceToken();
	// Constructs a new ResourceToken object with the specified type.
	ResourceToken(ResourceType);
	// Constructs a new ResourceToken object with the same type as the specified ResourceToken.
	ResourceToken(ResourceToken&);
	// Destructs this ResourceToken object.
	~ResourceToken();
	// Returns the type of this ResourceToken.
	int getType() const;
	// Writes this ResourceToken to the standard output stream
	void display() const;

private:
	
	ResourceType* type;

	ResourceToken::ResourceType randomType();

};
