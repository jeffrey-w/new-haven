#pragma once
#include "Building.h"
#include <vector>
#include <map>

using std::pair;
using std::vector;
using std::map;




class VGMap {
    class Circle {
        friend class VGMap;
    private:
        pair<int,int>* coordinates;//only usefull for testing, consider removing
        vector<Circle*> *adjCircles;
        Building *building;
        bool *visited;
        int number;

    public:
        Circle();
        Circle(pair<int,int>*);//remove if getting rid of coordinates member
        bool setBuilding(Building*);//TODO sure this isn't void?
    };

private:
    map<pair<int,int>, Circle*>* coordinatesMap;
    vector<Circle*>* circles;

public:
    VGMap();
    vector<Circle*>* getCircles();
    bool addCircle(int,int);
    bool addEdge(int,int,int,int);
    bool placeBuilding(int,int, Building*);
    void display();
    bool isConnected();
    void dfs(Circle*);
    bool isValid();

    //methods that go in driver later
    void buildMap();
};
