#pragma once

#include "Abilities.hpp"
#include <string.h>

class AbilityCreator {
    public:
        virtual Ability* createAbility(AbilityParameters& ap) = 0;
        virtual std::string getName() const = 0;
        virtual bool isUsingCoordinate() = 0;
        virtual ~AbilityCreator() {};
};

class DoubleDamageAbilityCreator : public AbilityCreator {
    public:
        DoubleDamageAbilityCreator() {};
        std::string getName() const override { return "Double Damage"; };
        bool isUsingCoordinate() override { return false; };
        Ability* createAbility(AbilityParameters& ap) override { return new DoubleDamage(ap.currentDamage); };
};

class ScannerAbilityCreator : public AbilityCreator {
    public:
        ScannerAbilityCreator() {};
        std::string getName() const override { return "Scanner"; };
        bool isUsingCoordinate() override { return true; };
        Ability* createAbility(AbilityParameters& ap) override { return new Scanner(ap.field, ap.coordinate); };
};

class GunblazeAbilityCreator : public AbilityCreator {
    public:
        GunblazeAbilityCreator() {};
        std::string getName() const override { return "Gunblaze"; };
        bool isUsingCoordinate() override { return false; };
        Ability* createAbility(AbilityParameters& ap) override { return new Gunblaze(ap.field); };
};
