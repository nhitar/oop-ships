#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "Painter.hpp"
#include "Player.hpp"
#include "Wrapper.hpp"
#include "Structs.hpp"
#include "Exceptions/UnableToOpenFileException.hpp"
#include "Exceptions/HashMismatchException.hpp"

#include <fstream>

class GameState {
    private:
        Player& player;
        Bot& bot;
        bool isAbilityUsed;
        int currentDamage;
        Coordinate coordinate;
    public:
        GameState(Player& player, Bot& bot) : player(player), bot(bot), isAbilityUsed(false), currentDamage(1) {};
        
        std::string getHash(const std::string& data);
        void placeShips(ShipManager& shipManager, Field& field);
        
        void loadGame();
        void saveGame();

        Player& getPlayer() { return this->player; };
        Bot& getBot() { return this->bot; };

        bool& getIsAbilityUsed() { return this->isAbilityUsed; };
        void setIsAbilityUsed(bool value) { this->isAbilityUsed = value; };
        
        int& getCurrentDamage() { return this->currentDamage; };
        void setCurrentDamage(int damage) { this->currentDamage = damage; };

        Coordinate& getCoordinate() { return this->coordinate; };
        void setCoordinate(Coordinate coordinate) { this->coordinate = coordinate; };
};