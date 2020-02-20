#pragma once

#include <map>
#include <set>
#include <vector>

#include "Building.h"

class VGMap {

    static constexpr int HEIGHT = 6, WIDTH = 5;

public:

    VGMap();
    VGMap(VGMap&) = delete; // Supress copy constructor
    ~VGMap();
    void setCicle(std::pair<int, int>, Building*);

private:

    class Node {

    public:

        static constexpr int WHITE = 0, GRAY = 1, BLACK = 2;

        Building* building;
        std::set<Node*>* adjacents;

        // Search Attributes.
        int* color;
        int* distance;
        Node* prev;

        Node();
        Node(Node&);
        void init(Building*, Building*, std::set<Node*>*);
    };

    std::map<std::pair<int,int>, Node*>* nodes;

    void build();
    void addNode(std::pair<int, int>);
    void addEdge(std::pair<int, int>, std::pair<int, int>);
    Node* nodeAt(std::pair<int, int>);
    std::pair<int, int> validateCoordinate(std::pair<int, int>);
    int search(Node*);
    void resetSearchAttributes(Building*);

};
