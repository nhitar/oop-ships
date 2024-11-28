#pragma once

#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/AbilityManager.hpp"
#include "../include/Painter.hpp"

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
    public:
        Player(ShipManager& shipManager, Field& field, AbilityManager& abilityManager)
            : Unit(shipManager, field), abilityManager(abilityManager) {}
        Player(const Player& other)
            : Unit(other.shipManager, other.field), abilityManager(other.abilityManager) {}
        Player& operator=(const Player& other) {
            if (this != &other) {
                this->shipManager = other.shipManager;
                this->field = other.field;
                this->abilityManager = other.abilityManager;
            }
            return *this;
        }

        ShipManager& getShipManager() override { return shipManager; };
        Field& getField() override { return field; };
        AbilityManager& getAbilityManager() { return abilityManager; };
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