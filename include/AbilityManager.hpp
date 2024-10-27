#pragma once

#include "Abilities.hpp"
#include "AbilityCreator.hpp"
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::queue<Abilities> abilities;
        Field& field;
    public:
        AbilityManager(Field& field);

        int getAbilityCount() const;
        Abilities front() const;
        void giveRandomAbility();

        void addAbility(Abilities ability);
        void useAbility(Coordinate coordinate = {-1, -1});
};