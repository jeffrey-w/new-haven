#pragma once

#include "AbstractToken.h"

// The token type that comprises HarvestTiles.
class ResourceToken : public AbstractToken {
  public:
    // The types a ResourceToken may have. (Corresponding BuildingTypes have corresponding
    // ordinals.)
    enum class ResourceType { SHEEP, STONE, TIMBER, WHEAT };

    // Constructs a new ResourceToken object with a random type.
    ResourceToken();
    // Constructs a new ResourceToken object with the specified type.
    ResourceToken(ResourceType);
    // Constructs a new ResourceToken object with the same type as the specified ResourceToken.
    ResourceToken(const ResourceToken&);
    // Destroys this ResourceToken object.
    ~ResourceToken();
    // Returns a deep copy of this ResourceToken.
    ResourceToken* clone() const override;
    // Returns the type of this ResourceToken.
    int getType() const override;

  protected:
    std::string toString() const override;

  private:
    ResourceType* type;

    static ResourceToken::ResourceType randomType();
};
