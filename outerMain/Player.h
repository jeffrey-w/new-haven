#pragma once

#include "VGMap.h"
#include "HarvestTile.h"
#include "Building.h"
#include "Resource.h"
#include "ScoringFacilities.h"



class Player {
private:
    //VGMap* villageBoard;
    std::vector<HarvestTile*>* harvestTiles;
    std::vector<Building*>* buildings;
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;
    static int resourceMarkers[];


public:
    Player();
    bool placeHarvestTile(int,int, HarvestTile*);
    Building* drawBuilding();
    HarvestTile* drawHarvestTile();
    //int* resourceTracker();//TODO find use for it since no needed right now
    bool buildVillage(int,int, Building*);
    //ResourceMarkers* calculateResources() TODO
    int calculateScore();
    VGMap* villageBoard;//TODO make private later, but now needed to print VGMap from main



};


