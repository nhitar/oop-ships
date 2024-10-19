#pragma once

#include "Field.hpp"
#include <random>
#include <string>
class Ability {
    public:
        virtual void implementAbility() = 0;
        virtual std::string getAbilityName() = 0;
        virtual void setField(Field* field) = 0;
        virtual void setCoordinate(Coordinate coordinate) = 0;
        virtual ~Ability() = default;
};

class DoubleDamage : public Ability {
    private:
        Field* field;
        Coordinate coordinate;
    public:
        DoubleDamage(Field* field, Coordinate coordinates);

        void setField(Field* field) override;
        void setCoordinate(Coordinate coordinate) override;
        std::string getAbilityName() override { return "Double Damage"; };

        void implementAbility() override;
};

class Scanner : public Ability {
    private:
        Field* field;
        Coordinate coordinate;
    public:
        Scanner(Field* field, Coordinate coordinates);
        
        void setField(Field* field) override;
        void setCoordinate(Coordinate coordinate) override;
        std::string getAbilityName() override { return "Scanner"; };

        void implementAbility() override;
};

class Gunblaze : public Ability {
    private:
        Field* field;
    public:
        Gunblaze(Field* field);
        
        std::string getAbilityName() override { return "Gunblaze"; };
        void setField(Field* field) override;

        void implementAbility() override;
};