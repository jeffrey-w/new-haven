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
    Player(const Player&);
    ~Player();
    VGMap* getVillageBoard();
    Building* drawBuilding(BuildingDeck*);
    HarvestTile* drawHarvestTile(HarvestTileDeck*);
    void buildVillage(Building*, std::pair<int, int>   );
    void placeHarvestTile(HarvestTile*, GBMap*, std::pair<int, int>);
    void resourceTracker(); // TODO what is this for?
    void calculateResources(GBMap*, std::pair<int, int>);
    int calculateScore();

private:
    
    VGMap* villageBoard;
    GatherFacility* gatherFacility;
    BuildFacility* buildFacility;

};


