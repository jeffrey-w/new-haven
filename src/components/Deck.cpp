#include "../maps/VGMap.h"
#include "Deck.h"

Deck<HarvestTile*>* harvestTileDeck() {
    int numTypes = AbstractToken::NUM_TYPES;
    Deck<HarvestTile*>* tiles = new Deck<HarvestTile*>();
    for (int i = 0; i < numTypes; i++) {
        for (int j = 0; j < numTypes; j++) {
            if (i != j) {
                // For each resource type i and each type j, add a new tile with three i and one j.
                tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j))));
                // For each resource type i and each type j, add a new tile with two i and two j.
                tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j)),
                        new ResourceToken(static_cast<ResourceType>(i)),
                        new ResourceToken(static_cast<ResourceType>(j))));
            }
        }
    }
    for (int i = 0; i < numTypes; i++) {
        for (int j = 0; j < numTypes; j++) {
            for (int k = 0; k < numTypes; k++) {
                if (!(i == j || i == k || j == k)) {
                    // For each resource type i, each type j, and each type k, add a new tile with two i (on the first
                    // column), one j, and one k.
                    tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                            new ResourceToken(static_cast<ResourceType>(j)),
                            new ResourceToken(static_cast<ResourceType>(i)),
                            new ResourceToken(static_cast<ResourceType>(k))));
                    if (j < k) {
                        // For each resource type i, each type j, and each type k, add a new tile with two i (on the
                        // main diagonal), one j, and one k.
                        tiles->add(new HarvestTile(new ResourceToken(static_cast<ResourceType>(i)),
                                new ResourceToken(static_cast<ResourceType>(j)),
                                new ResourceToken(static_cast<ResourceType>(k)),
                                new ResourceToken(static_cast<ResourceType>(i))));
                    }
                }
            }
        }
    }
    tiles->shuffle();
    return tiles;
}

Deck<Building*>* buildingDeck() {
    Deck<Building*>* buildings = new Deck<Building*>();
    for (int i = 0; i < VGMap::HEIGHT; i++) {
        for (int j = 0; j < VGMap::HEIGHT; j++) {
            for (int k = 0; k < AbstractToken::NUM_TYPES; k++) {
                BuildingType type = static_cast<BuildingType>(k);
                buildings->add(new Building(type, i + 1));
            }
        }
    }
    buildings->shuffle();
    return buildings;
}