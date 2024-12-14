#pragma once

#include "Game.hpp"
#include <map>

enum class Command {
    info = 0,
    attack = 1,
    ability = 2,
    load = 3,
    save = 4,
    quit = 5
};

class InputHandler {
    private:
        std::map <char, Command> commands;
    public:
        InputHandler();
        Command processCommandInput();
        Coordinate processCoordinateInput();
};