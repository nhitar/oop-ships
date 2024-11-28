#include "../include/Serialization.hpp"
#include <fstream>

void Serialization::to_json(ShipManager& shipManager, std::string key) {
    nlohmann::json jsm = nlohmann::json{};

    std::vector<Ship*> temp = shipManager.getShips();
    for (int i = 0; i < shipManager.getShipCount(); i++) {
        std::string key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp[i]->getLength()},
            {"horizontal", temp[i]->isHorizontal()},
            {"segments", nlohmann::json::array()}
        }; 

        std::vector<Segment*> tempShip = temp[i]->getSegments();

        for (int j = 0; j < temp[i]->getLength(); j++) {
            jsm[key]["segments"].push_back({
                {"x", tempShip[j]->coordinate.x},
                {"y", tempShip[j]->coordinate.y},
                {"health", tempShip[j]->health}
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
                {"value", char(temp[y*field.getRows() + x].value)} // уточнить значения
            };
        }
    }

    j[key] = jf;
}

void  Serialization::to_json(AbilityManager& abilityManager, std::string key) {
    nlohmann::json jam = nlohmann::json{};

    for (int i = 0; i < abilityManager.getAbilityCount(); i++) {
        jam["abilities"].push_back(
            {abilityManager.getCreator(i).getName()}
        );
    }

    j[key] = jam;
}