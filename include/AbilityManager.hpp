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
        ~AbilityManager();

        int getAbilityCount() const;
        AbilityCreator& getCreator(int index);
        void checkIfEmpty();

        void addAbility(AbilityCreator* creator);
        void giveRandomAbility();
        void useAbility(AbilityParameters& ap);
        void popAbility();
};
