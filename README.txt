welcome to new haven

According to the game rules, a player can place harvest squares from 0 to 4.

The map coordinates are the following:


 0,0 | 0,1 | 0,2 | 0,3 | 0,4

 1,0 | 1,1 | 1,2 | 1,3 | 1,4

 2,0 | 2,1 | 2,2 | 2,3 | 2,4

 3,0 | 3,1 | 3,2 | 3,3 | 3,4

 4,0 | 4,1 | 4,2 | 4,3 | 4,4


This is the default map for 2 players. The map will expand if there are more players (upto 4).

A player has a rotate option before placing a tile in order to yield the most harvest.

Before the setsquare, the rotate has parameters of 1, 2 or 3 to rotate the tile 90, 180 or 270 degrees respectively.

Internally, the setSquare function has assertions and validations to ensure valid position and rotate inputs.

Similarily, on the Village Game Map (VGMap), a player can set their building tiles (circles) to positions from 0 to 5 for height and 0 to 4 for width, for resources meadow, forest, stone and sheep.

The GBMapLoader can read in the "gmap.txt" and will throw an exception for invalid maps such as "gmap_bad.txt".

 
Each player is an object, each player will have a harvest_hand, building_hand and their own village_board.

Each player can draw_buildings, draw_harvest_tiles, build_villages and place_harvest_tiles. These are the utility functions for play.


The two decks, of harvest tiles and building tiles, are derived classes of an abstract Deck class. Fundamentally, each deck can add(tile) and draw. 
For programming assignment part 1, the harvest tiles are generated randomly and the exact cards will be implemented in the next assignment to follow the actual game tiles.


The scoring_facilities class has a count, that fundamentally counts the number of same resources attached to it. 
This is accomplished by a depth first search as well as applying a layer on top of the GBMap that color codes the nodes according to whether the node is to be searched (GRAY), 
the node is in the process of getting searched (BLACK) or if the node is to not be searched (RED). If the node is to be labeled in the future to be searched, it is designated (WHITE).
 This approach was influenced by the way the garbage collector in JAVA works.

