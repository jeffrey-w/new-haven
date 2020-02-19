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
	this->type = &type;
}

Resource::Resource(Resource& other) {
	type = new ResourceType(*other.type);
}

Resource::~Resource() {
	delete type;
}

Resource::ResourceType Resource::getType() const {
	return *type;
}
