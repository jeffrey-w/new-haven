#include "Dice.h"
#include <stdlib.h>
#include <ctime>

Dice::Dice() {
	srand(time(NULL));

	lastRoll = roll();

}

Dice::~Dice() {

}

int Dice::roll() {
	lastRoll = (rand() % 6 + 1);
	return lastRoll;
}

int Dice::getLastRoll() {
	return lastRoll;
}
