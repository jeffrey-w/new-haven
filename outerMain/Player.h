#pragma once

#include "Building.h"
#include "GBMap.h"
#include "HarvestTile.h"
#include "Resource.h"
#include "Resources.h"
#include "ScoringFacilities.h"
#include "VGMap.h"



class Player {

public:

    Player();
    void placeHarvestTile(HarvestTile*, GBMap*, std::pair<int, int>);
    Building* drawBuilding(BuildingDeck*);
    HarvestTile* drawHarvestTile(HarvestTileDeck*);
    void resourceTracker(); // TODO what is this for?
    void buildVillage(VGMap*);
    void calculateResources(GBMap*);

private:
    
    VGMap* villageBoard;
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;

};


