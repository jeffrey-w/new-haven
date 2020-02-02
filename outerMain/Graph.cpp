#include "Graph.h"
#include <iostream>

//default constructor
Node::Node(){
    adj=new set<Node*>;
}
Node::Node(pair<int,int>* coordinates): Node(){
    this->coordinates=coordinates;

}
void Node::setObject(GameObject * obj) {
    this->obj=obj;
}


Graph::Graph(){
    coordinatesMap=new map<pair<int,int>, Node*>;
    nodes=new vector<Node*>;
}

bool Graph::addNode(pair<int, int>* coord, Node* newNode) {
    if(coordinatesMap->count(*coord)>0){
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
    if(node1->adj->count(node2)>0){
        return false;
    }
    node1->adj->insert(node2);
    node2->adj->insert(node1);
}
void Graph::display() {
    for(Node* node : *nodes){
        cout<<node->coordinates->first<<","<<node->coordinates->second;
        for(Node* adjNode : *node->adj){
            cout<<"->"<<adjNode->coordinates->first<<","<<adjNode->coordinates->second;
        }
        cout<<endl;
    }
}

int Graph::search() {return 0;}


