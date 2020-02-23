#pragma once

#include "Building.h"
#include "GBMap.h"
#include "HarvestTile.h"
#include "Resources.h"
#include "ScoringFacilities.h"
#include "VGMap.h"



class Player {

public:

    Player();
    Building* drawBuilding(BuildingDeck*);
    HarvestTile* drawHarvestTile(HarvestTileDeck*);
    void buildVillage();
    void placeHarvestTile(HarvestTile*, GBMap*, std::pair<int, int>);
    void resourceTracker(); // TODO what is this for?
    void calculateResources(GBMap*, std::pair<int, int>);

private:
    
    VGMap* villageBoard;
    GatherFacility* gatherFacility; // TODO does this belong here
    BuildFacility* buildFacility; // TODO does this belong here

};


