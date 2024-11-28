#pragma once

#include "Abilities.hpp"
#include "AbilityCreator.hpp"
#include "Exceptions/NoAbilitiesAvailableException.hpp"
#include "AbilityParameters.hpp"

#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::queue<AbilityCreator*> abilities;
    public:
        AbilityManager();
        // AbilityManager(const AbilityManager& other)
        //     : abilities(other.abilities) {}
        // AbilityManager& operator=(const AbilityManager& other) {
        //     if (this != &other) {
        //         abilities = other.abilities;
        //    }
        //     return *this;
        // }

        int getAbilityCount() const;
        AbilityCreator& getCreator();
        void checkIfEmpty();

        void addAbility(AbilityCreator* creator);
        void giveRandomAbility();
        void useAbility(AbilityParameters& ap);
        void popAbility();
};
