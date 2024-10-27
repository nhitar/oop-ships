#pragma once

#include "Abilities.hpp"

enum class Abilities { DoubleDamage, Scanner, Gunblaze };

class AbilityCreator {
    public:
        virtual Ability* createAbility() = 0;
        virtual ~AbilityCreator() {};
};

class DoubleDamageAbilityCreator : public AbilityCreator {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        DoubleDamageAbilityCreator(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {};
        Ability* createAbility() override { return new DoubleDamage(this->field, this->coordinate); };
};

class ScannerAbilityCreator : public AbilityCreator {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        ScannerAbilityCreator(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {};
        Ability* createAbility() override { return new Scanner(this->field, this->coordinate); };
};

class GunblazeAbilityCreator : public AbilityCreator {
    private:
        Field& field;
    public:
        GunblazeAbilityCreator(Field& field) : field(field) {};
        Ability* createAbility() override { return new Gunblaze(this->field); };
};
