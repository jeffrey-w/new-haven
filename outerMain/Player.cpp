#include "Player.h"
int Player::resourceMarkers[]={50,50,50,50};

Player::Player(){
    villageBoard=new VGMap();
    std::vector<HarvestTile*>* harvestTiles=new vector<HarvestTile*>;
    std::vector<Building*>* buildings=new vector<Building*>;
    GatherFacility* gatherFacility=new GatherFacility;
    BuildFacility* buildFacility=new BuildFacility;
}



bool Player::buildVillage(int x, int y, Building* building) {
    if(building->getFaceUp() && building->getNumber()!=y){return false;}
    int buildingResource=building->getColour();
    if(resourceMarkers[buildingResource]<y){return false;}//not enough resources to build
    if(villageBoard->placeBuilding(x,y,building)){
        resourceMarkers[buildingResource]=resourceMarkers[buildingResource]-y;
        return true;
    }
    return false;
}