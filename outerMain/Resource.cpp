#include "Random.h"
#include "Resource.h"

bool Resource::equals(Resource* a, Resource* b) {
	if (!a) {
		return !b;
	}
	return a->getType() == b->getType();
}

Resource::Resource() : Resource(randomType()) {}

Resource::ResourceType Resource::randomType() {
	return static_cast<Resource::ResourceType>(Random::next(0, 3)); // TODO can bound be obtained programmatically?
}

Resource::Resource(ResourceType type) {
	placed = new bool(false);
	this->type = new ResourceType(type);
}

Resource::Resource(Resource& other) {
	placed = new bool(*other.placed);
	type = new ResourceType(*other.type);
}

Resource::~Resource() {
	delete type;
}

bool Resource::isPlaced() {
	return *placed;
}

Resource::ResourceType Resource::getType() const {
	return *type;
}
