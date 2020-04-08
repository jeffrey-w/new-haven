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

void Controller::run() {
	int exhausted;
	bool shipment;
	while (!game->gameOver()) {
		displayPossessions();
		// Prompt player to rotate tiles.
		while (in->decide("Player " + std::to_string(game->nextID())
			+ ", do you want to rotate any of your tiles?")) {
			if (!rotateSelection()) {
				break;
			}
		}
		// Play selected tile.
		shipment = placeSelection();
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
		game->endTurn(shipment);
	}
	// Determine and display winner(s).
	std::cout << "And our winner(s) is:\n";
	for (auto& id : game->winners()) {
		std::cout << "Player " << id << std::endl;
	}
	std::cout << "with " << game->highscore() << " villagers, " << game->buildingsPlayed()
		<< " buildings erected, and " << game->buidlingsLeft() << " buildings left.";
}

void Controller::displayPossessions() const {
	game->displayBoard();
	game->displayTiles();
	game->displayVillage();
	game->displayBuildings();
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
		if (selection == SHIPMENT) {
			int type = in->get<int>("Select resouce - 0: SH, 1: ST, 2: TI, 3: WH",
				"Invalid type.", true);
			if (in->cancelled()) {
				continue;
			}
			try {
				game->playShipment({ row, col }, type);
				game->displayBoard(type, { row, col });
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
