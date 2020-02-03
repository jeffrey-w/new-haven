#pragma once

#include "GBMap.h"
#include "VGMap.h"
#include "HarvestTile.h"
#include "Building.h"
#include "Resource.h"
#include "ScoringFacilities.h"


using std::vector;

class Player {
private:
    GBMap* gameBoard;//all players can share same gameBoard, no need to implement this for A1
    VGMap* villageBoard;
    vector<HarvestTile*>* harvestTiles;
    vector<Building*>* buildings;
    //ResourceMarkers TODO
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;


public:
    bool placeHarvestTile(int,int, HarvestTile*);
    Building* drawBuilding();
    HarvestTile* drawHarvestTile();
    //resourceTracker() it seemed resourceMarkers will track Resources so have to confirm with prof what is this for
    bool buildVillage(Building*);
    //ResourceMarkers* calculateResources() TODO implement Resourcemarkers first


};

