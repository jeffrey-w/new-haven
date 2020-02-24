#include <iostream>

#include "Random.h"
#include "ResourceToken.h"

ResourceToken::ResourceToken() : ResourceToken(randomType()) {}

ResourceToken::ResourceType ResourceToken::randomType() {
	return static_cast<ResourceToken::ResourceType>(Random::next(0, 3)); // TODO can bound be obtained programmatically?
}

ResourceToken::ResourceToken(ResourceType type) {
	this->type = new ResourceType(type);
}

ResourceToken::ResourceToken(const ResourceToken& other) {
	type = new ResourceType(*other.type);
}

ResourceToken::~ResourceToken() {
	delete type;
}

int ResourceToken::getType() const {
	return static_cast<int>(*type);
}

void ResourceToken::display() const {
	switch (*type) {
	case ResourceType::SHEEP:
		std::cout << "SH";
		break;
	case ResourceType::STONE:
		std::cout << "ST";
		break;
	case ResourceType::TIMBER:
		std::cout << "TI";
		break;
	case ResourceType::WHEAT:
		std::cout << "WH";
		break;
	}
}
