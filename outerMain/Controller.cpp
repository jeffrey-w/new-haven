#include "Controller.h"

Controller::Controller() {
	game = nullptr;
	in = new Input();
}

Controller::~Controller() {
	delete game;
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
}

void Controller::loop() {
	int exhausted;
	bool shipment;
	game->setup();
	while (!game->gameOver()) {
		game->displayBoard();
		game->displayTiles();
		while (in->decide("Player " + std::to_string(game->nextID())
			+ ", do you want to rotate any of your tiles?")) {
			if (!rotateSelection()) {
				break;
			}
		}
		shipment = placeSelection();
		for (int i = 0; i < game->numPlayers(); i++) {
			while (in->decide("Player " + std::to_string(game->nextID())
				+ ", do you want to play a building?", game->canPlay())) {
				if (!buildSelection()) {
					break;
				}
			}
			game->yield();
		}
		exhausted = game->exhausted();
		if (exhausted) {
			std::cout << "Player " << game->nextID() << ", you must draw " << exhausted
				<< " buildings.\n";
			selectBuilding(false);
			for (int i = 0; i < exhausted - 1; i++) {
				if (in->decide("Do you want to draw a building from the pool?")) {
					if (!(selectBuilding())) {
						i--;
						continue;
					}
				}
				else {
					game->drawFromDeck();
				}
			}
		}
		game->endTurn(shipment);
	}
	// Check for end game state
	// Calculate scores
	// If tie...
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
			game->displayTiles();
			return true;
		} catch (const std::exception& e) {
			std::cerr << e.what() << " Try again.\n";
		}
	} while (true);
}

bool Controller::placeSelection() {
	int selection, row, col;
	bool shipment = false;
	do {
		selection = in->get<int>("Select a tile", "Invalid selection.");
		row = in->get<int>("Select a row", "Invalid row.");
		col = in->get<int>("Select a column", "Invalid column");
		if (selection == 's' || selection == 'S') {
			int type = in->get<int>("Select resouce - 0: SH, 1: ST, 2: TI, 3: WH",
				"Invalid type.", true);
			if (in->cancelled()) {
				continue;
			}
			try {
				game->playShipment({ row, col }, type);
				// TODO display fake board
				shipment = true;
				break;
			} catch (const std::exception& e) {
				shipment = false;
				std::cerr << e.what() << " Try again.\n";
			}
		}
		else {
			try {
				game->playTile(selection, { row, col });
				game->displayBoard();
				break;
			} catch (const std::exception& e) {
				std::cerr << e.what() << " Try again.\n";
			}
		}
	} while (true);
	return shipment;
}

bool Controller::buildSelection() {
	int selection = 0, row, col;
	game->displayVillage();
	game->displayResources();
	game->displayBuildings();
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
			game->displayBuildings();
		}
	} while (true);
}

bool Controller::selectBuilding(bool canCancel) {
	int selection = 0;
	game->displayPool();
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
