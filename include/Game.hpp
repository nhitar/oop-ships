#pragma once

#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"
#include "../include/Player.hpp"
#include "../include/Abilities.hpp"
#include "../include/AbilityManager.hpp"
#include "../include/Exceptions/InvalidShipSizeException.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        bool isPlayerWin;
    public:
        Game(Player player, Bot bot) 
            : player(player), bot(bot), isPlayerWin(false) {}
        void playRound();
        void resetBot();
        void resetGame();
        void startGame();
};
