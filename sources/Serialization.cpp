#include "../include/Serialization.hpp"
#include <fstream>

void Serialization::to_json(ShipManager& shipManager, std::string key) {
    nlohmann::json jsm = nlohmann::json{};

    for (int i = 0; i < shipManager.getShipCount(); i++) {
        Ship& temp = shipManager.getShipByIndex(i);
        std::string key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp.getLength()},
            {"horizontal", temp.isHorizontal()},
            {"segments", nlohmann::json::array()}
        }; 

        for (int j = 0; j < temp.getLength(); j++) {
            Segment* tempSegment = temp.getSegment(j);
            jsm[key]["segments"].push_back({
                {"x", tempSegment->coordinate.x},
                {"y", tempSegment->coordinate.y},
                {"health", tempSegment->health}
            });
        }
    }

    j[key] = jsm;
}

void Serialization::to_json(Field& field, std::string key) {
    nlohmann::json jf = nlohmann::json{};

    jf["rows"] = field.getRows();
    jf["columns"] = field.getColumns();

    std::vector<Cell> temp = field.getField();
    for (int y = 0; y < field.getRows(); y++) {
        for (int x = 0; x < field.getColumns(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            jf[key] = {
                {"x", temp[y*field.getRows() + x].coordinate.x},
                {"y", temp[y*field.getRows() + x].coordinate.y},
                {"state", temp[y*field.getRows() + x].state}, // уточнить значения
                {"value", temp[y*field.getRows() + x].value} // уточнить значения
            };
        }
    }

    j[key] = jf;
}

void  Serialization::to_json(AbilityManager& abilityManager, std::string key) {
    nlohmann::json jam = nlohmann::json{};

    for (int i = 0; i < abilityManager.getAbilityCount(); i++) {
        jam["abilities"].push_back(
            abilityManager.getCreator(i).getName()
        );
    }
    if (abilityManager.getAbilityCount() == 0) {
        jam["abilities"].push_back("");
    }
    j[key] = jam;
}