#pragma once

#include "Game.h"
#include "util/Input.h"
#include "views/GameView.h"

// Maps user input to model input, and updates view.
class Controller {

	static constexpr int SHIPMENT = 3;

public:

	// Constructs a new Controller object.
	Controller();
	// Suppress copy constructor.
	Controller(const Controller&) = delete;
	// Deletes this Controller.
	~Controller();
	// Initializes a Game from user input.
	void initGame();
	// Adds Players to this Controller's Game.
	void inputIDs();
	// Runs a Game of New Haven.
	void run();

private:

	Game* game;
	GameView* view;
	Input* in;

	bool rotateSelection();
	void placeSelection();
	bool buildSelection();
	bool selectBuilding(bool = true);

};

