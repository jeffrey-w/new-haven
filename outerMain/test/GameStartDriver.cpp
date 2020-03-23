#include <iostream>
#include <sstream>
#include <string>

#include "../Game.h"
#include "../util/Debug.h"
#include "GameStartDriver.h"

static Game* initGame();

void testGameStart() {
    std::cout << "Running Game start tests:\n";
    Game* game = initGame();
    std::cout << "Initializing game board...\n";
    game->displayBoard();
    std::cout << "Initializing resource markers...\n";
    game->displayCount();
    std::cout << "Initializing players...\n";
    game->displayerPlayers();
    std::cout << "Initializing face up pool...\n";
    game->displayPool();
    std::cout << "Harvest tiles left after dealing to players...\n";
    std::cout << game->tilesLeft() << '\n';
    std::cout << "Buildings left after dealing to players and face up pool...\n";
    std::cout << game->buildingsLeft() << '\n';
    delete game;
}

Game* initGame() {
    int numPlayers = 0;
    Game* game = nullptr;
    do {
        std::cout << "Enter number of players: ";
        std::string input;
        std::getline(std::cin, input);
        std::stringstream(input) >> numPlayers;
        try {
            game = new Game(numPlayers);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Accept default number of players ("
                << std::to_string(Game::DEFAULT_NUM_PLAYERS) << ")? Y/n: ";
            switch (std::cin.get()) {
            case 'Y':
            case 'y':
                game = new Game();
                break;
            case 'N':
            case 'n':
                std::cout << "Okay, try again.\n";
                break;
            default:
                std::cout << "Did not understantd, try again.\n";
            }
            std::cin.ignore();
        }
    } while (!game);
    return game;
}
