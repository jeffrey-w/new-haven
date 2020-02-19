#pragma once

// Instances of the Resource class inhabit spaces on a GBMap.
class Resource {

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
	// Returns true iff this Resource inhabits a GBMap, otherwise false,
	bool isPlaced();
	// Returns the type of this Resource.
	ResourceType getType() const;

private:

	bool* placed;
	ResourceType* type;

	Resource::ResourceType randomType();

};
