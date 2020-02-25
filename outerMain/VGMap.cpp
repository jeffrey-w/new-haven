#include <queue>
#include "VGMap.h"
#include <iostream>

using std::map;
using std::pair;
using std::queue;
using std::cout;

VGMap::VGMap() {
    graph = TokenGraph::gridOf(HEIGHT, WIDTH);
    typePlaced=new std::array<bool,4>();
}

VGMap::~VGMap() {
	delete graph;
	delete typePlaced;
}

void VGMap::setCircle( Building* building, bool faceDown, std::pair<int, int> circle) {
    validateCircle(circle);
    int buildType=static_cast<int>(building->getType());
    if((*typePlaced)[buildType] && !(graph->adjacentHolds(circle, buildType))){
        throw std::logic_error("Building must be placed adjacent to same type");
    }
    if(!faceDown && building->getValue()!=HEIGHT-circle.first)
    {
        throw std::logic_error("Face Up buildings must be placed in appropriate row");
    }
	graph->setTokenAt(building->tokenize(), circle);
}

void VGMap::validateCircle(std::pair<int, int> circle) {
	if(circle.first<0 || circle.first>HEIGHT-1 || circle.second<0 || circle.second>WIDTH-1){
	    throw std::invalid_argument("Invalid coordinates");
	}
}

void VGMap::display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            BuildingToken* building = static_cast<BuildingToken*>(graph->tokenAt({ i, j }));
            if (building) {
                building->display();
                cout << '\t';
            }
            else {
                cout << "-\t";
            }
        }
        cout << "\n\n";
    }
}
