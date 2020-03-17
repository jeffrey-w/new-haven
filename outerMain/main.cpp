#include <iostream>
#include <sstream>
#include <string>

#include "Game.h"
#include "test/Drivers.h"

static Game* initGame();

int main() {
    testGBMap();
    testVGMap();
    testGBMapLoader();
    testVGMapLoader();
    testPlayer();
    testResources();
    testScoringFacilities();
    Game* game = initGame();
    game->displayBoard();
    delete game;
    return 0;
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
