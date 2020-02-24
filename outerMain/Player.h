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
    Building* drawBuilding(BuildingDeck*);
    HarvestTile* drawHarvestTile(HarvestTileDeck*);
    void buildVillage(Building*, bool faceDown, std::pair<int, int>   );
    void placeHarvestTile(HarvestTile*, GBMap*, std::pair<int, int>);
    void resourceTracker(); // TODO what is this for?
    void calculateResources(GBMap*, std::pair<int, int>);
    int calculateScore();

    VGMap* villageBoard;//TODO return to private after done testing in main
private:
    
    //VGMap* villageBoard;
    GatherFacility* gatherFacility; // TODO does this belong here
    BuildFacility* buildFacility; // TODO does this belong here

};


