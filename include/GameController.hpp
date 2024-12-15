#pragma once

#include "Game.hpp"
#include "InputHandler.hpp"

template <class Input, class Output>
class GameController {
    private:
        Game& game;
        Input& input;
        Output& output;
    public:
        GameController(Game& game, Input& input, Output& output) 
            : game(game), input(input), output(output) {};
        void run();
};