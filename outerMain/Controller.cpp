#include "Controller.h"

Controller::Controller() {
	game = nullptr;
	view = nullptr;
	in = new Input();
}

Controller::~Controller() {
	delete game;
	delete view;
	delete in;
}

void Controller::initGame() {
	do {
		try {
			game = new Game(in->get<int>("Enter number of players", "Must enter a number."));
		} catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			if (in->decide("Accept default number of players (" 
				+ std::to_string(Game::DEFAULT_NUM_PLAYERS) + ")?")) {
				game = new Game();
			}
		}
	} while (!game);
}

void Controller::inputIDs() {
	for (int i = 0; i < game->numPlayers(); i++) {
		do {
			try {
				game->addPlayer(in->get<long>("Enter ID for player "
					+ std::to_string(i + 1), "Invalid ID."));
				break;
			} catch (const std::invalid_argument& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		} while (true);
	}
	view = gameView(game);
}

void Controller::run() {
	int exhausted;
	while (!game->gameOver()) {
		view->showBoard();
		view->showTiles();
		view->showVillage();
		view->showBuildings();
		// Prompt player to rotate tiles.
		while (in->decide("Player " + std::to_string(game->nextID())
			+ ", do you want to rotate any of your tiles?")) {
			if (!rotateSelection()) {
				break;
			}
		}
		// Play selected tile.
		placeSelection();
		// Play buildings and share resources with other players.
		for (int i = 0; i < game->numPlayers(); i++) {
			while (in->decide("Player " + std::to_string(game->nextID())
				+ ", do you want to play a building?")) {
				if (!game->canPlay()) {
					std::cout << "You have no more valid moves.\n";
					break;
				}
				if (!buildSelection()) {
					break;
				}
			}
			game->yield();
			view->rotate();
		}
		// Draw new buildings.
		if ((exhausted = game->exhausted()) && !game->gameOver()) {
			std::cout << "Player " << game->nextID() << ", you must draw " << exhausted
				<< " buildings.\n";
			selectBuilding(false);
			for (int i = 0; i < exhausted - 1; i++) {
				if (in->decide("Do you want to draw a building from the pool?")) {
					if (!(selectBuilding())) {
						i--;
					}
				}
				else {
					game->drawFromDeck();
				}
			}
		}
		// Housekeeping before next turn.
		game->endTurn();
		view->rotate();
	}
	// Determine and display winner(s).
	std::cout << "And our winner(s) is:\n";
	for (auto& id : game->winners()) {
		std::cout << "Player " << id << std::endl;
	}
	std::cout << "with " << game->highscore() << " villagers, " << game->buildingsPlayed()
		<< " buildings erected, and " << game->buidlingsLeft() << " buildings left.";
}

bool Controller::rotateSelection() {
	int selection;
	do {
		selection = in->get<int>("Select a tile to rotate", "Invalid selection.", true);
		if (in->cancelled()) {
			return false;
		}
		try {
			game->rotateTile(selection);
			view->showTiles();
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
				game->playShipment({ row, col }, type);
				break;
			} catch (const std::exception& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		}
		else {
			try {
				game->playTile(selection, { row, col });
				break;
			} catch (const std::exception& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		}
	} while (true);
	view->showBoard();
}

bool Controller::buildSelection() {
	int selection = 0, row, col;
	view->showVillage();
	view->showResources();
	view->showBuildings();
	do {
		selection = in->get<int>("Select a building", "Ivalid selection.", true);
		if (in->cancelled()) {
			return false;
		}
		row = in->get<int>("Select a row", "Invalid row.");
		col = in->get<int>("Select a column", "Invalid column.");
		try {
			game->playBuilding(selection, { row, col });
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
			view->showBuildings();
		}
	} while (true);
}

bool Controller::selectBuilding(bool canCancel) {
	int selection = 0;
	view->showPool();
	do {
		selection = in->get<int>("Select a building", "Invalid selection.", canCancel);
		if (in->cancelled()) {
			return false;
		}
		try {
			game->drawFromPool(selection);
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
		}
	} while (true);
}
