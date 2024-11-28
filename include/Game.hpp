#pragma once

#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"
#include "../include/Player.hpp"
#include "../include/GameState.hpp"
#include "../include/Abilities.hpp"
#include "../include/AbilityManager.hpp"
#include "../include/Exceptions/InvalidShipSizeException.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        GameState gameState;
        bool isPlayerWin;
        bool isBotWin;
    public:
        Game(Player player, Bot bot, GameState gameState) 
            : player(player), bot(bot), gameState(gameState), isPlayerWin(false), isBotWin(false) {}
            
        void usePlayerAbility();
        void doPlayerAttack();
        void doBotAttack();

        void playTurns();
        void resetBot();
        void resetGame();
        void isGameEnded();

        void loadGame(const std::string& file);
        void saveGame(const std::string& file);

};
