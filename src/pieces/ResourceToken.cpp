#include <sstream>

#include "../util/Random.h"
#include "ResourceToken.h"

ResourceToken::ResourceToken() : ResourceToken(randomType()) {
}

ResourceToken::ResourceType ResourceToken::randomType() {
    return static_cast<ResourceType>(Random::next(0, AbstractToken::NUM_TYPES - 1));
}

ResourceToken::ResourceToken(ResourceType type) {
    this->type = type;
}

ResourceToken::ResourceToken(const ResourceToken& other) : AbstractToken(other) {
    type = other.type;
}

ResourceToken* ResourceToken::clone() const {
    return new ResourceToken(*this);
}

int ResourceToken::getType() const {
    return static_cast<int>(type);
}

std::string ResourceToken::toString() const {
    std::ostringstream stream;
    switch (type) {
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
    return stream.str();
}
