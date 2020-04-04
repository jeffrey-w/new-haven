#pragma once

#include "Game.h"
#include "util/Input.h"

class Controller {

	static constexpr int SHIPMENT = 3;

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

