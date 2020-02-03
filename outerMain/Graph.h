#include <map>
#include <vector>
#include "GameObject.h"
#include <set>

using namespace std;


class Node{
    friend class Graph;
private:
    pair<int,int>* coordinates;
    set<Node*>* adj;
    GameObject* obj;
    bool* visited;

public:
    Node();
    Node(pair<int,int>*);
    void setObject(GameObject*);
    GameObject* getObject(Node*);
};



class Graph{
public:
    map<pair<int,int>, Node*>* coordinatesMap;
    vector<Node*>* nodes;

public:
    Graph();

    bool addNode(pair<int,int>*, Node*);
    bool addEdge(pair<int,int>*, pair<int,int>*);
    void display();
    bool isConnected();
    void dfs(Node*);
};