#include <queue>
#include "VGMap.h"
#include <iostream>

using std::map;
using std::pair;
using std::queue;
using std::cout;

VGMap::VGMap() {
    graph=TokenGraph::gridOf(HEIGHT, WIDTH);
}

VGMap::~VGMap() {
	delete graph;
}

void VGMap::setCircle( Building* building, std::pair<int, int> circle) {
	graph->setTokenAt(building->tokenize(), circle);
}

/*VGMap::Node* VGMap::nodeAt(std::pair<int, int> coordinate) {
	return nodes->at(validateCoordinate(coordinate));
}*/

/*std::pair<int, int> VGMap::validateCoordinate(std::pair<int, int> coordinate) {
	//TODO
}*/

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
