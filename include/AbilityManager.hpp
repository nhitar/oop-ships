#pragma once

#include "Abilities.hpp"
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::deque<Ability*> abilities;
        int abilityCount;
    public:
        AbilityManager();
        
        std::deque<Ability*>* getDeque();

        int getAbilityCount() const;
        void setAbilityCount(int count);
        void addAbility();
};