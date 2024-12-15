#pragma once

#include "Game.hpp"
#include "Command.hpp"
#include <map>

class InputHandler {
    private:
        std::map <char, Command> commands;
    public:
        InputHandler();
        void setCommands(std::map <char, Command> newCommands);
        Command processCommandInput();
        Coordinate processCoordinateInput();
};