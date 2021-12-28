#pragma once

#include "GameBuilder.h"
#include "util/Input.h"
#include "views/GameView.h"

// Maps user input to model input, and updates view.
class Controller {

    static constexpr int SHIPMENT = 3, ROW_OFFSET = 65;
    static std::string WINNER_PROMPT;

  public:
    // Constructs a new Controller object.
    Controller();
    // Suppress copy constructor.
    Controller(const Controller&) = delete;
    // Deletes this Controller.
    ~Controller();
    // Initializes a Game from user input.
    void initGame();
    // Runs a Game of New Haven.
    void run();

  private:
    Game* model;
    GameView* view;
    Input in;

    bool acceptDefaultNumberOfPlayers();
    void inputIDs(GameBuilder*);
    bool rotateSelection();
    void placeSelection();
    bool buildSelection();
    bool selectBuilding(bool = true);
    std::string current();
};
