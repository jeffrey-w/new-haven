welcome to new haven

According to the game rules, a player can place harvest squares from 0 to 4.

The map coordinates are the following:


 0,0 | 0,1 | 0,2 | 0,3 | 0,4

 1,0 | 1,1 | 1,2 | 1,3 | 1,4

 2,0 | 2,1 | 2,2 | 2,3 | 2,4

 3,0 | 3,1 | 3,2 | 3,3 | 3,4

 4,0 | 4,1 | 4,2 | 4,3 | 4,4


This is the default map for 2 players. The map will expand if there are more players (up to 4).

A player has a rotate option before placing a tile in order to yield the most harvest.

Internally, the setSquare function has assertions and validations to ensure valid position inputs.

Similarily, on the Village Game Map (VGMap), a player can set their buildings to positions from 0 to 5 for height and 0 to 4 for width, for resources meadow, forest, stone and sheep.

The GBMapLoader can read in the "gmap.txt" and will throw an exception for invalid maps such as "gmap_bad.txt".
The VGMapLoader provides similar functionality for VGMaps.
 
Each player is an object, each player will have a harvest hand, building hand and their own village board.

Each player can draw buildings, draw harvest tiles, build villages and place harvest tiles. These are the utility functions for play.


The two decks, of harvest tiles and building tiles, are instantiations of a Deck class. Fundamentally, each deck can add(piece) and draw. 

For programming assignment part 1, the harvest tiles are generated randomly. For assignment 2, correct pieces are implemented in the.

The gather facility class has a count that fundamentally counts the number of same resources attached to it. This is accomplished by a breadth first search as well as applying a layer on top of the GBMap that color codes its nodes according to whether the node is to be searched (WHITE), the node is in the process of getting searched (GRAY), if the node is already searched (BLACK), or if the node is to not be searched (RED). This approach was influenced by the mark and sweep garbage collection algorithm.

To build from Visual Studio:

Unzip the contents of your download.
Double click the file outerMain.sln in the project's root directory, or open it from Visual Studio.
Press Ctrl+Shift+B to build the project.
