#pragma once

#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"
#include "../include/Player.hpp"
#include "../include/Abilities.hpp"
#include "../include/AbilityManager.hpp"
#include "../include/Exceptions/InvalidShipSizeException.hpp"

// #include "json.hpp"

class Game {
    private:
        Player player;
        Bot bot;
        bool isPlayerWin;
        bool isBotWin;
    public:
        Game(Player player, Bot bot) 
            : player(player), bot(bot), isPlayerWin(false), isBotWin(false) {}
            
        void usePlayerAbility();
        void doPlayerAttack();
        void doBotAttack();

        void playTurns();
        void resetBot();
        void resetGame();
        void isGameEnded();

        // friend void to_json(nlohmann::json& j, const Game& game);
        // friend void from_json(nlohmann::json& j, const Game& game);
};
