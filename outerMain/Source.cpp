
#include <iostream>
#include <vector>
#include "Graph.h"
#include "HarvestTile.h"
#include "GBMap.h"

using std::cout;
using std::cin;
using std::vector;



int main()
{
    cout << "Hi New Haven!\n";
    Graph* g=new Graph();

    pair<int, int>* free_square_0 = new pair<int, int>(0, 0);
    Node* node_0 = new Node(free_square_0);
    HarvestTile* ht_0 = new HarvestTile();
    node_0->setTile(ht_0);   

    pair<int, int>* free_square_1 = new pair<int, int>(0, 1);
    Node* node_1 = new Node(free_square_1);
    HarvestTile* ht_1 = new HarvestTile();
    node_1->setTile(ht_1);

    g->addNode(free_square_0, node_0);
    g->addNode(free_square_1, node_1);

    g->addEdge(free_square_0, free_square_1);




    //for(int i=0; i<4; i++){
    //    for(int j=0; j<4; j++) {
    //        pair<int, int>* p = new pair<int,int>(i, j);
    //        Node* newNode=new Node(p);
    //        HarvestTile* ht=new HarvestTile();
    //        newNode->setTile(ht);
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


    g->display();

    // TEST GBMap
    GBMap gbmap(2);
    cout << gbmap.search({ 0, 0 }) << "\n";
    gbmap.display();

    /*HarvestTile* test = new HarvestTile();
    test->printTile();
    test->changeTileOrientation(3);
    test->printTile();*/

    
    system("pause");

    return 0;
}