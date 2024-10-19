#pragma once

#include "Field.hpp"
#include <random>
#include <string>
class Ability {
    public:
        virtual void implementAbility(Field* field, Coordinate coordinate) = 0;
        virtual std::string getAbilityName() = 0;
        virtual ~Ability() = default;
};

class DoubleDamage : public Ability {
    public:
        void implementAbility(Field* field, Coordinate coordinate) override;
        std::string getAbilityName() override { return "Double Damage"; };
};

class Scanner : public Ability {
    public:
        void implementAbility(Field* field, Coordinate coordinate) override;
        std::string getAbilityName() override { return "Scanner"; };
};

class Gunblaze : public Ability {
    public:
        void implementAbility(Field* field, Coordinate coordinate) override;
        std::string getAbilityName() override { return "Gunblaze"; };
};