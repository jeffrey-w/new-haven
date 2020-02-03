#pragma once
#include "Building.h"
#include <vector>
#include <map>


class Circle {
    friend class VGMap;
private:
    std::pair<int,int>* coordinates;//only usefull for testing, consider removing
    std::vector<Circle*> *adjCircles;
    Building *building;
    bool *visited;
    int number;

public:
    Circle();
    Circle(std::pair<int,int>*);//remove if getting rid of coordinates member
    bool setBuilding(Building*);
};

class VGMap {
private:
    std::map<std::pair<int,int>, Circle*>* coordinatesMap;
    std::vector<Circle*>* circles;

public:
    VGMap();
    std::vector<Circle*>* getCircles();
    bool addCircle(int,int);
    bool addEdge(int,int,int,int);
    bool placeBuilding(int,int, Building*);
    void display();
    bool isConnected();
    void dfs(Circle*);
    bool isValid();
};
