#pragma once

#include "Game.hpp"
#include "InputHandler.hpp"

template <class Input, class Output>
class GameController {
    private:
        Game& game;
        GameState& gameState;
        Input& inputHandler;
        Output& outputHandler;
    public:
        GameController(Game& game, GameState& gameState, Input& inputHandler, Output& outputHandler) 
            : game(game), gameState(gameState), inputHandler(inputHandler), outputHandler(outputHandler) {};
        void run();
};