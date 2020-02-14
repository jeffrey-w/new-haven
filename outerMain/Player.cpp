#include "Player.h"

using std::vector;

int Player::resourceMarkers[]={200,200,200,200};

Player::Player(){
    villageBoard=new VGMap();
    harvestTiles=new vector<HarvestTile*>;
    buildings=new vector<Building*>;
    gatherFacility=new GatherFacility;
    buildFacility=new BuildFacility(villageBoard);
}



bool Player::buildVillage(int x, int y, Building* building) {//TODO make sure placed next to similar color
    if(building->getFaceUp() && building->getNumber()!=y){return false;}
    int buildingResource=building->getColour();
    if(resourceMarkers[buildingResource]<y){return false;}//not enough resources to build
    if(villageBoard->placeBuilding(x,y,building)){
        resourceMarkers[buildingResource]=resourceMarkers[buildingResource]-y;
        return true;
    }
    return false;
}

int Player::calculateScore() {
   return buildFacility->calculateVillageScore();
}