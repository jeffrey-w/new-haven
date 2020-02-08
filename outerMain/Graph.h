#include <map>
#include <vector>
#include <set>

using namespace std;


class Node{
    friend class Graph;
private:
    pair<int,int>* coordinates;
    set<Node*>* adj;
    bool* visited;

public:
    Node();
    Node(pair<int,int>*);
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