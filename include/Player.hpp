#pragma once

#include "ShipManager.hpp"
#include "Field.hpp"
#include "AbilityManager.hpp"
#include "Painter.hpp"
#include "AbilityParameters.hpp"

class Unit {
    protected:
        ShipManager& shipManager;
        Field& field;
    public:
        Unit(ShipManager& shipManager, Field& field)
            : shipManager(shipManager), field(field) {}

        virtual ShipManager& getShipManager() = 0;
        virtual Field& getField() = 0;
        virtual ~Unit() {};
};

class Player : public Unit {
    private:
        AbilityManager& abilityManager;
        int currentDamage;
    public:
        Player(ShipManager& shipManager, Field& field, AbilityManager& abilityManager)
            : Unit(shipManager, field), abilityManager(abilityManager), currentDamage(1) {}
        Player(const Player& other)
            : Unit(other.shipManager, other.field), abilityManager(other.abilityManager), currentDamage(other.currentDamage) {}
        Player& operator=(const Player& other) {
            if (this != &other) {
                this->shipManager = other.shipManager;
                this->field = other.field;
                this->abilityManager = other.abilityManager;
                this->currentDamage = other.currentDamage;
            }
            return *this;
        }

        ShipManager& getShipManager() override { return shipManager; };
        Field& getField() override { return field; };
        AbilityManager& getAbilityManager() { return abilityManager; };
        int& getCurrentDamage() { return currentDamage; };
        void setCurrentDamage(int damage) { currentDamage = damage; };
};

class Bot : public Unit {
    public:
        Bot(ShipManager& shipManager, Field& field)
            : Unit(shipManager, field) {}
        Bot(const Bot& other)
            : Unit(other.shipManager, other.field) {}

        Bot& operator=(const Bot& other) {
            if (this != &other) {
                this->shipManager = other.shipManager;
                this->field = other.field;
            }
            return *this;
        }

        ShipManager& getShipManager() override { return shipManager; };
        Field& getField() override { return field; };
};