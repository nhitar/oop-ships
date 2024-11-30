#pragma once

#include "ShipManager.hpp"
#include "Field.hpp"
#include "AbilityManager.hpp"

#include <string.h>
#include <nlohmann/json.hpp>

class Deserialization {
    private:
        nlohmann::json& j; 
    public:
        Deserialization(nlohmann::json& j) : j(j) {};

        void from_json(ShipManager& shipManager, std::string key);
        void from_json(Field& field, std::string key);
        void from_json(AbilityManager& abilityManager, std::string key);
};