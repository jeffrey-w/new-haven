cmake_minimum_required(VERSION 3.2)
project(New-Haven VERSION 1.0.0 LANGUAGES CXX)
add_executable(new-haven
    Controller.cpp
    Game.cpp
    main.cpp
    components/Resources.cpp
    components/ScoringFacilities.cpp
    maps/GBMap.cpp
    maps/TokenGraph.cpp
    maps/VGMap.cpp
    observers/Observable.cpp
    pieces/AbstractToken.cpp
    pieces/Building.cpp
    pieces/BuildingToken.cpp
    pieces/HarvestTile.cpp
    pieces/ResourceToken.cpp
    players/Player.cpp
    players/Roster.cpp
    util/Input.cpp
    util/Random.cpp
    views/GameView.cpp
    views/PlayerView.cpp
    views/RosterView.cpp
    views/View.cpp
)
