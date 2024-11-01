#pragma once

#include "Field.hpp"
#include <random>
#include <string>
class Ability {
    public:
        virtual void implementAbility() = 0;
        virtual ~Ability() = default;
};

class DoubleDamage : public Ability {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        DoubleDamage(Field& field, Coordinate coordinate);

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
