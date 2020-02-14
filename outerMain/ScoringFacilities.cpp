#include "ScoringFacilities.h"






BuildFacility::BuildFacility(){}
BuildFacility::BuildFacility(VGMap* map):BuildFacility() {
    this->map=map;
}
int BuildFacility::calculateVillageScore() {
    int score=0;
    bool emptyCircle;
    bool faceDown;
    //calculate score for the rows
    for(int y=1; y<=6; y++){
        emptyCircle=false;
        faceDown=false;
        for(int x=1; x<=5; x++){
            if(map->getCircle(x,y)->getBuilding()== nullptr){
                emptyCircle=true;
                break;
            }
            if(map->getCircle(x,y)->getBuilding()->getFaceUp()==false){
                faceDown=true;
            }
        }
        if(emptyCircle){
            continue;
        }
        score+=(faceDown)? y : 2*y;
    }
    //calculate score for the columns
    for(int x=1; x<=5; x++){
        emptyCircle=false;
        faceDown=false;
        for(int y=1; y<=6; y++){
            if(map->getCircle(x,y)->getBuilding()== nullptr){
                emptyCircle=true;
                break;
            }
            if(map->getCircle(x,y)->getBuilding()->getFaceUp()==false){
                faceDown=true;
            }
        }
        if(emptyCircle){
            continue;
        }
        switch(x){
            case 1:
            case 5:
                score+=(faceDown)? 5 : 10;
                break;
            case 2:
            case 4:
                score+=(faceDown)? 4 : 8;
                break;
            case 3:
                score+=(faceDown)? 3 : 6;
        }
    }
    return score;
}