#include "Graph.h"
#include <iostream>

//>>>>>>>>>>>>>Node class<<<<<<<<<<<<<
//constructors
Node::Node(){
    adj=new set<Node*>;
    obj= nullptr;
    visited=new bool();
}
Node::Node(pair<int,int>* coordinates): Node(){
    this->coordinates=coordinates;

}
//setter and getter for GameObject. GameObject should be a ResourceTile or Building
GameObject* Node::getObject(Node * node) {
    return node->obj;
}
void Node::setObject(GameObject * obj) {
    this->obj=obj;
}

//>>>>>>>>>>>>>>Graph class<<<<<<<<<<<<<
//constructor
Graph::Graph(){
    coordinatesMap=new map<pair<int,int>, Node*>;
    nodes=new vector<Node*>;
}

bool Graph::addNode(pair<int, int>* coord, Node* newNode) {
    if(coordinatesMap->count(*coord)>0) {
        return false;
    }
    coordinatesMap->insert({*coord, newNode});
    nodes->push_back(newNode);
    return true;
}
bool Graph::addEdge(pair<int, int>* coord1, pair<int, int>* coord2 ) {
    if(coordinatesMap->count(*coord1)==0 || coordinatesMap->count(*coord2)==0){
        return false;
    }
    Node* node1=coordinatesMap->find(*coord1)->second;
    Node* node2=coordinatesMap->find(*coord2)->second;
    node1->adj->insert(node2);
    node2->adj->insert(node1);
}
//temporary method to display connections in graph
void Graph::display() {
    for(Node* node : *nodes){
        cout<<node->coordinates->first<<","<<node->coordinates->second;
        for(Node* adjNode : *node->adj){
            cout<<"->"<<adjNode->coordinates->first<<","<<adjNode->coordinates->second;
        }
        cout<<endl;
    }
}
//checks to see if graph is connected
bool Graph::isConnected() {
    for(Node* node: *nodes){
        *node->visited=false;
    }
    dfs(nodes->front());
    for(Node* node: *nodes){
        if(*node->visited==false) return false;
    }
    return true;
}
void Graph::dfs(Node* node) {
    if(*node->visited==true) return;
    *node->visited=true;
    for(Node* adjNode: *node->adj){
        dfs(adjNode);
    }
}
