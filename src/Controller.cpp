#include <cctype>

#include "Controller.h"

std::string Controller::WINNER_PROMPT = "And the final scores are...";

Controller::Controller() {
    model = nullptr;
    view = nullptr;
}

Controller::~Controller() {
    delete model;
    delete view;
}

void Controller::initGame() {
    do {
        try {
            model = new Game(in.get<int>("Enter number of players", "Must enter a number.", 0));
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            if (Input::decide("Accept default number of players (" + std::to_string(Game::DEFAULT_NUM_PLAYERS) + ")?")) {
                model = new Game();
            }
        }
    } while (!model);
}

void Controller::inputIDs() {
    for (int i = 0; i < model->numPlayers(); i++) {
        do {
            try {
                model->addPlayer(in.get<long>("Enter ID for player " + std::to_string(i + 1), "Invalid ID.", 0));
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
    std::string _current;
    while (!model->gameOver()) {
        view->showBoard();
        view->showTiles();
        view->showVillage();
        view->showBuildings();
        _current = current();
        // Rotate tiles.
        while (Input::decide(_current + ", do you want to rotate any tiles?")) {
            if (!rotateSelection()) {
                break;
            }
        }
        // Select and play tile.
        placeSelection();
        // Play buildings and share resources with other players.
        for (int i = 0; i < model->numPlayers(); i++) {
            view->showVillage();
            view->showBuildings();
            while (Input::decide(_current + ", do you want to play a building?")) {
                if (model->canPlay()) {
                    if (!buildSelection()) {
                        break;
                    }
                } else {
                    std::cout << "You have no more valid moves.\n";
                    break;
                }
            }
            model->yield();
            view->rotate();
            _current = current();
        }
        // Draw buildings.
        if ((exhausted = model->exhausted()) && !model->gameOver()) {
            view->showPool();
            std::cout << _current << ", you must draw " << exhausted << " buildings.\n";
            selectBuilding(false);
            for (int i = 0; i < exhausted - 1; i++) {
                if (Input::decide("Do you want to draw a building from the pool?")) {
                    if (!(selectBuilding())) {
                        i--;
                    }
                } else {
                    model->drawFromDeck();
                }
            }
        }
        // Housekeeping before next turn.
        model->endTurn();
        view->rotate();
    }
    // Display winner(s).
    view->showStats(&WINNER_PROMPT);
}

bool Controller::rotateSelection() {
    int selection;
    do {
        selection = in.get<int>("Select a tile to rotate", "Invalid selection.", 0, true);
        if (in.cancelled()) {
            return false;
        }
        try {
            model->rotateTile(--selection);
            return true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << " Try again.\n";
        }
    } while (true);
}

void Controller::placeSelection() {
    int selection, row, col;
    do {
        selection = in.get<int>("Select a tile", "Invalid selection.", 0);
        row = toupper(in.get<char>("Select a row", "Invalid row.", 0)) - ROW_OFFSET;
        col = in.get<int>("Select a column", "Invalid column", 0);
        if (selection == SHIPMENT) {
            int type = in.get<int>("Select resouce - 1: SH, 2: ST, 3: TI, 4: WH", "Invalid type.", 0, true);
            if (in.cancelled()) {
                continue;
            }
            try {
                model->playShipment({row, --col}, --type);
                break;
            } catch (const std::exception& e) {
                std::cerr << e.what() << " Try again.\n";
            }
        } else {
            try {
                model->playTile(--selection, {row, --col});
                break;
            } catch (const std::exception& e) {
                std::cerr << e.what() << " Try again.\n";
            }
        }
    } while (true);
}

bool Controller::buildSelection() {
    int selection, row, col;
    do {
        selection = in.get<int>("Select a building", "Ivalid selection.", 0, true);
        if (in.cancelled()) {
            return false;
        }
        row = toupper(in.get<char>("Select a row", "Invalid row.", 0)) - ROW_OFFSET;
        col = in.get<int>("Select a column", "Invalid column.", 0);
        try {
            model->playBuilding(--selection, {row, --col});
            return true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << " Try again.\n";
        }
    } while (true);
}

bool Controller::selectBuilding(bool canCancel) {
    int selection = 0;
    do {
        selection = in.get<int>("Select a building", "Invalid selection.", 0, canCancel);
        if (in.cancelled()) {
            return false;
        }
        try {
            model->drawFromPool(--selection);
            return true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << " Try again.\n";
        }
    } while (true);
}

std::string Controller::current() {
    return "Player " + std::to_string(model->nextID());
}
