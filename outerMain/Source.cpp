
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
    srand(time(0));
    cout << "Hi New Haven!\n";
    
    // TEST GBMap
    GBMap gbmap(2);
    cout << gbmap.search({ 0, 0 }) << "\n";
    gbmap.display();

    /*HarvestTile* test = new HarvestTile();
    test->printTile();
    HarvestTile* test2 = new HarvestTile();
    test2->printTile();
    HarvestTile* test3 = new HarvestTile();
    test3->printTile();*/

    /*Deck* test = new Deck();

    Building* testBuild = test->giveBuilding();
    testBuild->printBuilding();*/

    /*Building* test = new Building(Building::FOREST, 4);
    test->printBuilding();*/
    
    system("pause");

    return 0;
}