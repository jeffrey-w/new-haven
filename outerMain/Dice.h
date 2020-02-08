#pragma once
class Dice {
public:
	Dice();
	~Dice();
	int roll();
	int getLastRoll();

private:
	int lastRoll;
};