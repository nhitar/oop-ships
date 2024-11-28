#pragma once

#include "Field.hpp"
#include "AbilityParameters.hpp"
#include <random>
#include <string>
class Ability {
    public:
        virtual void implementAbility() = 0;
        virtual ~Ability() {};
};

class DoubleDamage : public Ability {
    private:
        int& currentDamage;
    public:
        DoubleDamage(int& currentDamage);

        void implementAbility() override;
};

class Scanner : public Ability {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        Scanner(Field& field, Coordinate coordinate);

        void implementAbility() override;
};

class Gunblaze : public Ability {
    private:
        Field& field;
    public:
        Gunblaze(Field& field);

        void implementAbility() override;
};
