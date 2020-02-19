#pragma once

#include "Building.h"
#include "Deck.h"
#include "GBMap.h"
#include "HarvestTile.h"
#include "Resource.h"
#include "ScoringFacilities.h"
#include "VGMap.h"



class Player {

public:

    Player();
    void placeHarvestTile(HarvestTile*, GBMap*, std::pair<int, int>);
    Building* drawBuilding();
    HarvestTile* drawHarvestTile();
    void resourceTracker(); // TODO what is this for?
    void buildVillage(VGMap*, ScoringFacility*);
    void calculateResources(GBMap*, ResourceMarkers*);

private:
    
    VGMap* villageBoard;
    Deck* harvestTiles;
    Deck* buildings;
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;

};


