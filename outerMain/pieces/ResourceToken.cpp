#include <iostream>

#include "../util/Debug.h"
#include "../util/Random.h"
#include "ResourceToken.h"

using ResourceType = ResourceToken::ResourceType;

ResourceToken::ResourceToken() : ResourceToken(randomType()) {}

ResourceToken::ResourceType ResourceToken::randomType() {
	return static_cast<ResourceType>(Random::next(0, 3));
}

ResourceToken::ResourceToken(ResourceType type) {
	this->type = new ResourceType(type);
}

ResourceToken::ResourceToken(const ResourceToken& other) : AbstractToken(other) {
	type = new ResourceType(*other.type);
}

ResourceToken::~ResourceToken() {
	delete type;
}

int ResourceToken::getType() const {
	return static_cast<int>(*type);
}

std::ostream& operator<<(std::ostream& stream, const ResourceToken& token) {
	switch (*token.type) {
	case ResourceType::SHEEP:
		stream << "SH";
		break;
	case ResourceType::STONE:
		stream << "ST";
		break;
	case ResourceType::TIMBER:
		stream << "TI";
		break;
	case ResourceType::WHEAT:
		stream << "WH";
		break;
	}
	return stream;
}
