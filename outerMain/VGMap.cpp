#include "VGMap.h"

using std::map;
using std::pair;
using std::vector;
using std::cout;

//constructor
VGMap::Circle::Circle(){
    adjCircles=new vector<Circle*>;
    building= nullptr;
    visited=new bool();
}
VGMap::Circle::Circle(pair<int,int>* coord):Circle(){
    coordinates=coord;
    number=coord->second;
}

Building* VGMap::Circle::getBuilding() { return building;}

bool VGMap::Circle::setBuilding(Building* building) {
    this->building=building;
    return true;
}


VGMap::VGMap(){
    coordinatesMap=new map<pair<int,int>, Circle*>;
    circles=new vector<Circle*>;
    buildMap();
}
vector<VGMap::Circle *> * VGMap::getCircles() {
    return circles;
}

VGMap::Circle* VGMap::getCircle(int x, int y){
    return coordinatesMap->find({x,y})->second;
}

bool VGMap::addCircle(int x, int y) {
    if(coordinatesMap->count({x,y})>0){
        return false; //circle already created at this coordinate
    }
    pair<int,int>* p=new pair<int,int>(x,y);
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
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <=5; j++) {
            Circle* circle = coordinatesMap->find({j,i})->second;
            if (circle->building!= nullptr) {
                circle->building->printBuilding();
                cout<<"\t";
            }
            else {
                std::cout << "-\t\t";
            }
        }
        std::cout << "\n\n";
    }


    /*    for(Circle* circle: *circles){
        cout<<circle->coordinates->first<<","<<circle->coordinates->second;
        for(Circle* adjCircle: *circle->adjCircles){
            cout<<"->"<<adjCircle->coordinates->first<<","<<adjCircle->coordinates->second;
        }
        cout<<std::endl;
    }*/
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


// METHODS THAT WILL GO IN DRIVER LATER
void VGMap::buildMap(){
    //add Circles at appropriate coordinates
    for(int i=1; i<=5; i++){
        for(int j=1; j<=6; j++){
            addCircle(i,j);
        }
    }
    //add edges
    for(int i=1; i<=5; i++){
        for(int j=1; j<=6; j++){
            if(i<5) {
                addEdge(i, j, i + 1, j);
            }
            if(j<6){
                addEdge(i,j,i,j+1);
            }
        }
    }
}
