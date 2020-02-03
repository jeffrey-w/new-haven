#include "GBMap.h"

GBMap::GBMap(int numPlayers) {
	space = new Graph();
	// TODO switch on numPlayers for number of spaces
}


//commenting out since no search() method, use isConnected() from Graph and vector.size() to find out size
/*
bool GBMap::isConnected(int numPlayers) { // TODO refactor magic constants
	int numSpaces = space->search();
	switch (numPlayers) {
	case 2:
		return numSpaces == 25;
	case 3:
		return numSpaces == 35;
	case 4:
		return numSpaces == 45;
	}
}
*/
