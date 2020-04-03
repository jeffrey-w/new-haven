#pragma once

#include "Game.h"
#include "util/Input.h"

class Controller {

	static constexpr unsigned int SHIP_MASK = 'S' | 's';

public:

	Controller();
	Controller(const Controller&) = delete;
	~Controller();
	void initGame();
	void inputIDs();
	void loop();

private:

	Game* game;
	Input* in;

	bool rotateSelection();
	bool placeSelection();
	bool buildSelection();
	bool selectBuilding(bool = true);

};

