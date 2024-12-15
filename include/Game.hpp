#pragma once

#include "Ship.hpp"
#include "ShipManager.hpp"
#include "Field.hpp"
#include "Painter.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Abilities.hpp"
#include "AbilityManager.hpp"
#include "Observer.hpp"
#include "Exceptions/InvalidShipSizeException.hpp"
#include "Exceptions/InvalidCoordinateException.hpp"
#include "Exceptions/HashMismatchException.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        GameState gameState;
        Painter painter;
        std::vector<Observer*> observers;
    public:
        Game(Player player, Bot bot, GameState gameState, Painter painter)
            : player(player), bot(bot), gameState(gameState), painter(painter) {}
            
        void usePlayerAbility();
        void doPlayerAttack();
        void doBotAttack();

        // void startGame();
        void resetBot();
        void resetGame();

        void addObserver(Observer* observer);

        void loadGame();
        void saveGame();

        GameState& getGameState() { return gameState; };
};
