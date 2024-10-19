#pragma once

#include "Abilities.hpp"
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::deque<std::unique_ptr<Ability>> abilities;
        int abilityCount;
    public:
        AbilityManager();
        
        std::deque<std::unique_ptr<Ability>>* getDeque();

        int getAbilityCount() const;
        void setAbilityCount(int count);
        void addAbility();
};