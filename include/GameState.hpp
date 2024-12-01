#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "Painter.hpp"
#include "Player.hpp"
#include "Wrapper.hpp"

#include <fstream>

class GameState {
    public:
        Player& player;
        Bot& bot;
        Painter& painter;
    public:
        GameState(Player& player, Bot& bot, Painter& painter) : player(player), bot(bot), painter(painter) {};
        void saveGame(const std::string& file);
        void loadGame(const std::string& file);
};