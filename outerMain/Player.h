#pragma once

#include "VGMap.h"
#include "HarvestTile.h"
#include "Building.h"
#include "Resource.h"
#include "ScoringFacilities.h"


class Player {
private:
    VGMap* villageBoard;
    std::vector<HarvestTile*>* harvestTiles;
    std::vector<Building*>* buildings;
    //ResourceMarkers TODO
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;


public:
    Player();
    bool placeHarvestTile(int,int, HarvestTile*);
    Building* drawBuilding();
    HarvestTile* drawHarvestTile();
    //resourceTracker() it seemed resourceMarkers will track Resources so have to confirm with prof what is this for
    bool buildVillage(Building*);
    //ResourceMarkers* calculateResources() TODO implement Resourcemarkers first


};

