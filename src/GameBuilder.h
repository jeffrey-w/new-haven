#pragma once

#include <map>

#include "Game.h"
#include "players/Player.h"

class GameBuilder {

    public:
    
        GameBuilder(int);
        ~GameBuilder() = default;
        int addPlayer(long);
        bool atCapacity() const;
        Game* build();

    private:

        GBMap* board;
        Deck<HarvestTile*>* tiles;
        Deck<Building*>* buildings;
        BuildingPool* pool;
        Roster* players;

        void setup();

};