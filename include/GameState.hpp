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
    public:
        GameState(Player& player, Bot& bot) : player(player), bot(bot) {};
        
        void placeShips(ShipManager& shipManager, Field& field);
        
        void loadGame(const std::string& file);
        void saveGame(const std::string& file);
};