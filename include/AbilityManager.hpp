#pragma once

#include "Abilities.hpp"
#include "AbilityCreator.hpp"
#include "Exceptions/NoAbilitiesAvailableException.hpp"
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
        AbilityManager(const AbilityManager& other)
            : abilities(other.abilities), field(other.field) {}
        AbilityManager& operator=(const AbilityManager& other) {
            if (this != &other) {
                abilities = other.abilities;
           }
            return *this;
        }

        int getAbilityCount() const;
        Abilities front() const;
        void checkIfEmpty();

        void addAbility(Abilities ability);
        void giveRandomAbility();
        void useAbility(Coordinate coordinate = {-1, -1});
        void popAbility();
};
