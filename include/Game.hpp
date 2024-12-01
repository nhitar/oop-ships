#pragma once

#include "Ship.hpp"
#include "ShipManager.hpp"
#include "Field.hpp"
#include "Painter.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Abilities.hpp"
#include "AbilityManager.hpp"
#include "Exceptions/InvalidShipSizeException.hpp"
#include "Exceptions/InvalidCoordinateException.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        GameState gameState;
        Painter painter;
        bool isPlayerWin;
        bool isBotWin;
    public:
        Game(Player player, Bot bot, GameState gameState, Painter painter)
            : player(player), bot(bot), gameState(gameState), painter(painter), isPlayerWin(false), isBotWin(false) {}
            
        void usePlayerAbility();
        void doPlayerAttack();
        void doBotAttack();

        void playTurns();
        void resetBot();
        void resetGame();
        bool isGameEnded();

        void loadGame(const std::string& file);
        void saveGame(const std::string& file);

};
