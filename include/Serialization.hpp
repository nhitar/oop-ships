#pragma once

#include "ShipManager.hpp"
#include "Field.hpp"
#include "AbilityManager.hpp"

#include <string.h>
#include <nlohmann/json.hpp>

class Serialization {
    private:
        nlohmann::json& j; 
    public:
        Serialization(nlohmann::json& j) : j(j) {};

        void to_json(ShipManager& shipManager, std::string key);
        void to_json(Field& field, std::string key);
        void to_json(AbilityManager& abilityManager, std::string key);
};