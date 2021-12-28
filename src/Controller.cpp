#include <cctype>

#include "Controller.h"

Controller::Controller() {
    model = nullptr;
    view = nullptr;
}

Controller::~Controller() {
    delete model;
    delete view;
}

void Controller::initGame() {
    GameBuilder* builder = nullptr;
    do {
        try {
            builder = new GameBuilder(in.get<int>(
                "Enter number of players", "Must enter a number.", 0));
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            if (acceptDefaultNumberOfPlayers()) {
                builder = new GameBuilder(Game::DEFAULT_NUM_PLAYERS);
            }
        }
    } while (!builder);
    inputIDs(builder);
    model = builder->build();
    view = gameView(model);
}

bool Controller::acceptDefaultNumberOfPlayers() {
    return Input::decide(
        "Accept default number of players (" + std::to_string(Game::DEFAULT_NUM_PLAYERS) + ")?");
}

void Controller::inputIDs(GameBuilder* builder) {
    int numPlayers = 0;
    while (!builder->atCapacity()) {
loop:
        try {
            numPlayers = builder->addPlayer(
                in.get<long>("Enter ID for player " + std::to_string(numPlayers + 1), "Invalid ID.", 0));
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << " Try again.\n";
            goto loop;
        }
    }
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
    view->showStats("And the final scores are...");
}

bool Controller::rotateSelection() {
loop:
    int selection = in.get<int>("Select a tile to rotate", "Invalid selection.", 0, true);
    if (in.cancelled()) {
        return false;
    }
    try {
        model->rotateTile(--selection);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << " Try again.\n";
        goto loop;
    }

}

void Controller::placeSelection() {
loop:
    int selection = in.get<int>("Select a tile", "Invalid selection.", 0);
    int row = toupper(in.get<char>("Select a row", "Invalid row.", 0)) - ROW_OFFSET;
    int col = in.get<int>("Select a column", "Invalid column", 0);
    if (selection == SHIPMENT) {
        int type = in.get<int>("Select resouce - 1: SH, 2: ST, 3: TI, 4: WH", "Invalid type.", 0, true);
        if (in.cancelled()) {
            goto loop;
        }
        try {
            model->playShipment({row, --col}, --type);
        } catch (const std::exception& e) {
            std::cerr << e.what() << " Try again.\n";
            goto loop;
        }
    } else {
        try {
            model->playTile(--selection, {row, --col});
        } catch (const std::exception& e) {
            std::cerr << e.what() << " Try again.\n";
            goto loop;
        }
    }
}

bool Controller::buildSelection() {
loop:
    int selection = in.get<int>("Select a building", "Ivalid selection.", 0, true);
    if (in.cancelled()) {
        return false;
    }
    int row = toupper(in.get<char>("Select a row", "Invalid row.", 0)) - ROW_OFFSET;
    int col = in.get<int>("Select a column", "Invalid column.", 0);
    try {
        model->playBuilding(--selection, {row, --col});
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << " Try again.\n";
        goto loop;
    }
}

bool Controller::selectBuilding(bool canCancel) {
loop:
    int selection = in.get<int>("Select a building", "Invalid selection.", 0, canCancel);
    if (in.cancelled()) {
        return false;
    }
    try {
        model->drawFromPool(--selection);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << " Try again.\n";
        goto loop;
    }
}

std::string Controller::current() {
    return "Player " + std::to_string(model->nextID());
}
