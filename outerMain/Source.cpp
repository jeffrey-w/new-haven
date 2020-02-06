
#include <iostream>
#include <vector>
#include "Graph.h"
#include "HarvestTile.h"

using std::cout;
using std::cin;
using std::vector;



int main()
{
    cout << "Hi New Haven!\n";



    Graph* g=new Graph();
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++) {
            pair<int, int>* p = new pair<int,int>(i, j);
            Node* newNode=new Node(p);
            HarvestTile* ht=new HarvestTile();
            newNode->setObject(ht);
            g->addNode(p, newNode);

        }
    }
    for(int i=0; i<3; i++) {
        for (int j = 0; j < 4; j++) {
            pair<int, int> *p1 = new pair<int, int>(i, j);
            pair<int, int> *p2 = new pair<int, int>(i + 1, j);

            g->addEdge(p1, p2);
        }
    }
    for(int i=0; i<4; i++) {
        for (int j = 0; j < 3; j++) {
            pair<int, int> *p1 = new pair<int, int>(i, j);
            pair<int, int> *p2 = new pair<int, int>(i, j+1);

            g->addEdge(p1, p2);
        }
    }


    g->display();

    /*HarvestTile* test = new HarvestTile();
    test->printTile();
    test->changeTileOrientation(1);
    test->printTile();*/

    
    system("pause");

    return 0;
}