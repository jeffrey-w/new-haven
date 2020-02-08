
#include <iostream>
#include <vector>
#include "Graph.h"
#include "HarvestTile.h"
#include "GBMap.h"
#include "Deck.h"
#include "Building.h"

using std::cout;
using std::cin;
using std::vector;



int main()
{
    cout << "Hi New Haven!\n";
    //Graph* g=new Graph();
    //for(int i=0; i<4; i++){
    //    for(int j=0; j<4; j++) {
    //        pair<int, int>* p = new pair<int,int>(i, j);
    //        Node* newNode=new Node(p);
    //        HarvestTile* ht=new HarvestTile();
    //        newNode->setObject(ht);
    //        g->addNode(p, newNode);

    //    }
    //}
    //for(int i=0; i<3; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        pair<int, int> *p1 = new pair<int, int>(i, j);
    //        pair<int, int> *p2 = new pair<int, int>(i + 1, j);

    //        g->addEdge(p1, p2);
    //    }
    //}
    //for(int i=0; i<4; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        pair<int, int> *p1 = new pair<int, int>(i, j);
    //        pair<int, int> *p2 = new pair<int, int>(i, j+1);

    //        g->addEdge(p1, p2);
    //    }
    //}


    //g->display();

    //// TEST GBMap
    //GBMap gbmap(2);
    //cout << gbmap.search({ 0, 0 }) << "\n";
    //gbmap.display();

    /*HarvestTile* test = new HarvestTile();
    test->printTile();
    test->changeTileOrientation(3);
    test->printTile();*/

    Deck* test = new Deck();

    Building* testBuild = test->giveBuilding();
    testBuild->printBuilding();

    /*Building* test = new Building(Building::FOREST, 4);
    test->printBuilding();*/
    
    system("pause");

    return 0;
}