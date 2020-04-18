#include "Controller.h"

Controller::Controller() {
	model = nullptr;
	view = nullptr;
	in = new Input();
}

Controller::~Controller() {
	delete model;
	delete view;
	delete in;
}

void Controller::initGame() {
	do {
		try {
			model = new Game(in->get<int>("Enter number of players", "Must enter a number."));
		} catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			if (in->decide("Accept default number of players (" 
				+ std::to_string(Game::DEFAULT_NUM_PLAYERS) + ")?")) {
				model = new Game();
			}
		}
	} while (!model);
}

void Controller::inputIDs() {
	for (int i = 0; i < model->numPlayers(); i++) {
		do {
			try {
				model->addPlayer(in->get<long>("Enter ID for player "
					+ std::to_string(i + 1), "Invalid ID."));
				break;
			} catch (const std::invalid_argument& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		} while (true);
	}
	view = gameView(model);
}

void Controller::run() {
	int exhausted;
	while (!model->gameOver()) {
		view->showBoard();
		view->showTiles();
		view->showVillage();
		view->showBuildings();
		// Prompt player to rotate tiles.
		while (in->decide("Player " + std::to_string(model->nextID())
			+ ", do you want to rotate any of your tiles?")) {
			if (rotateSelection()) {
				view->showTiles();
			}
			else {
				break;
			}
		}
		// Play selected tile.
		placeSelection();
		view->showBoard();
		// Play buildings and share resources with other players.
		for (int i = 0; i < model->numPlayers(); i++) {
			while (in->decide("Player " + std::to_string(model->nextID())
				+ ", do you want to play a building?")) {
				if (model->canPlay()) {
						view->showVillage();
						view->showResources();
						view->showBuildings();
					if (!buildSelection()) {
						break;
					}
				}
				else {
					std::cout << "You have no more valid moves.\n";
					break;
				}
			}
			model->yield();
			view->rotate();
		}
		// Draw new buildings.
		if ((exhausted = model->exhausted()) && !model->gameOver()) {
			std::cout << "Player " << model->nextID() << ", you must draw " << exhausted
				<< " buildings.\n";
			view->showPool();
			selectBuilding(false);
			for (int i = 0; i < exhausted - 1; i++) {
				view->showPool();
				if (in->decide("Do you want to draw a building from the pool?")) {
					if (!(selectBuilding())) {
						i--;
					}
					else {
						view->showPool();
					}
				}
				else {
					model->drawFromDeck();
				}
			}
		}
		// Housekeeping before next turn.
		model->endTurn();
		view->rotate();
	}
	// Determine and display winner(s).
	std::cout << "And our winner(s) is:\n";
	// TODO game winning logic with observer
}

bool Controller::rotateSelection() {
	int selection;
	do {
		selection = in->get<int>("Select a tile to rotate", "Invalid selection.", true);
		if (in->cancelled()) {
			return false;
		}
		try {
			model->rotateTile(selection);
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
		}
	} while (true);
}

void Controller::placeSelection() {
	int selection, row, col;
	do {
		selection = in->get<int>("Select a tile", "Invalid selection.");
		row = in->get<int>("Select a row", "Invalid row.");
		col = in->get<int>("Select a column", "Invalid column");
		if (selection == SHIPMENT) {
			int type = in->get<int>("Select resouce - 0: SH, 1: ST, 2: TI, 3: WH",
				"Invalid type.", true);
			if (in->cancelled()) {
				continue;
			}
			try {
				model->playShipment({ row, col }, type);
				break;
			} catch (const std::exception& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		}
		else {
			try {
				model->playTile(selection, { row, col });
				break;
			} catch (const std::exception& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		}
	} while (true);
}

bool Controller::buildSelection() {
	int selection = 0, row, col;
	do {
		selection = in->get<int>("Select a building", "Ivalid selection.", true);
		if (in->cancelled()) {
			return false;
		}
		row = in->get<int>("Select a row", "Invalid row.");
		col = in->get<int>("Select a column", "Invalid column.");
		try {
			model->playBuilding(selection, { row, col });
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
		}
	} while (true);
}

bool Controller::selectBuilding(bool canCancel) {
	int selection = 0;
	do {
		selection = in->get<int>("Select a building", "Invalid selection.", canCancel);
		if (in->cancelled()) {
			return false;
		}
		try {
			model->drawFromPool(selection);
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
		}
	} while (true);
}
