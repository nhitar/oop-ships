#pragma once

#include "Wrapper.hpp"
#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "Player.hpp"

#include <fstream>

class GameState {
    public:
        Player& player;
        Bot& bot;
    public:
        GameState(Player& player, Bot& bot) : player(player), bot(bot) {};
        void saveGame(const std::string& file);
        void loadGame(const std::string& file);
};