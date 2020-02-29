#pragma once

#include "maps/GBMap.h"
#include "maps/VGMap.h"
#include "pieces/Building.h"
#include "pieces/HarvestTile.h"
#include "Resources.h"
#include "ScoringFacilities.h"



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
    void resourceTracker(GatherFacility*, int, int); // TODO what is this for?
    void calculateResources(GBMap*, std::pair<int, int>, GatherFacility*);
    int calculateScore();

private:
    
    Hand* hand;
    VGMap* villageBoard;
    BuildFacility* buildFacility;

};


