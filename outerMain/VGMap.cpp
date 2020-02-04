#include "VGMap.h"


//constructor
Circle::Circle(){
    adjCircles=new std::vector<Circle*>;
    building= nullptr;
    visited=new bool();
}
Circle::Circle(std::pair<int,int>* coord):Circle(){
    coordinates=coord;
    number=coord->second;
}

bool Circle::setBuilding(Building* building) {
    this->building=building;
    return true;
}


VGMap::VGMap(){
    coordinatesMap=new std::map<std::pair<int,int>, Circle*>;
    circles=new std::vector<Circle*>;
}
std::vector<Circle *> * VGMap::getCircles() {
    return circles;
}
bool VGMap::addCircle(int x, int y) {
    if(coordinatesMap->count({x,y})>0){
        return false;//circle already created at this coordinate
    }
    std::pair<int,int>* p=new std::pair<int,int>(x,y);
    Circle* newCircle=new Circle(p);
    coordinatesMap->insert({{x,y}, newCircle});
    circles->push_back(newCircle);
    return true;
}
bool VGMap::addEdge(int x1, int y1, int x2, int y2) {
    if(coordinatesMap->find({x1,y1})==coordinatesMap->end() || coordinatesMap->find({x2,y2})==coordinatesMap->end()){
        return false;
    }
    Circle* circle1=coordinatesMap->find({x1,y1})->second;
    Circle* circle2=coordinatesMap->find({x2,y2})->second;
    circle1->adjCircles->push_back(circle2);
    circle2->adjCircles->push_back(circle1);
}
bool VGMap::placeBuilding(int x, int y, Building* building) {
    Circle* circle=coordinatesMap->find({x,y})->second;
    if(circle->building!=nullptr){
        return false; //a building is already placed at this coordinate
    }
    circle->setBuilding(building);
}
//temporary method to display connections in VGMap
void VGMap::display() {
    for(Circle* circle: *circles){
        cout<<circle->coordinates->first<<","<<circle->coordinates->second;
        for(Circle* adjCircle: *circle->adjCircles){
            cout<<"->"<<adjCircle->coordinates->first<<","<<adjCircle->coordinates->second;
        }
        cout<<std::endl;
    }
}

//checks to see if graph is connected
bool VGMap::isConnected() {
    for(Circle* circle: *circles){
        *circle->visited=false;
    }
    dfs(circles->front());
    for(Circle* circle: *circles){
        if(*circle->visited==false) return false;
    }
    return true;
}
void VGMap::dfs(Circle* circle) {
    if(*circle->visited==true) return;
    *circle->visited=true;
    for(Circle* adjCircle: *circle->adjCircles){
        dfs(adjCircle);
    }
}
/*TODO
bool VGMap::isValid(){

}*/
