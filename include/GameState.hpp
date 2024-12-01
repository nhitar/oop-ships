#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "Painter.hpp"
#include "Player.hpp"
#include "Wrapper.hpp"
#include "Exceptions/UnableToOpenFileException.hpp"

#include <fstream>

class GameState {
    private:
        Player& player;
        Bot& bot;
        bool isAbilityUsed;
    public:
        GameState(Player& player, Bot& bot) : player(player), bot(bot), isAbilityUsed(false) {};
        
        void placeShips(ShipManager& shipManager, Field& field);
        
        void loadGame(const std::string& file);
        void saveGame(const std::string& file);

        Player& getPlayer() { return this->player; };
        Bot& getBot() { return this->bot; };
        bool& getIsAbilityUsed() { return this->isAbilityUsed; };
        void setIsAbilityUsed(bool value) { this->isAbilityUsed = value; };
};