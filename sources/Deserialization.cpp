#include "../include/Deserialization.hpp"

void Deserialization::from_json(ShipManager& shipManager, std::string key) {
    const auto& jsm = j.at(key);
    std::vector<int> shipSizes;

    for (const auto& jship : jsm) {
        shipSizes.push_back(jship.at("length"));
    }
    shipManager = ShipManager(shipSizes.size(), shipSizes);

    for (size_t i = 0; i < shipSizes.size(); i++) {
        std::string key = "ship" + std::to_string(i);
        Ship& ship = shipManager.getShipByIndex(i);
        if (jsm.at(key).at("horizontal") == true) {
            ship.setOrientation(Orientation::Horizontal);
        }
        else {
            ship.setOrientation(Orientation::Vertical);
        }

        for (int j = 0; j < shipSizes[i]; j++) {
            
            Segment* segment = ship.getSegment(j);

            segment->health = jsm.at(key).at("segments").at(j).at("health");
            segment->coordinate.x = jsm.at(key).at("segments").at(j).at("x");
            segment->coordinate.y = jsm.at(key).at("segments").at(j).at("y");
        }
    }

    int shipsAlive = shipSizes.size();
    for (size_t i = 0; i < shipSizes.size(); i++) {
        Ship& ship = shipManager.getShipByIndex(i);
        if (ship.isDestroyed()) {
            shipsAlive--;
        }
    }
    shipManager.setShipsAlive(shipsAlive);
}

void Deserialization::from_json(Field& field, std::string key) {
    const auto& jf = j.at(key);
    field = Field(jf.at("rows"), jf.at("columns"));

    for (int y = 0; y < field.getRows(); y++) {
        for (int x = 0; x < field.getColumns(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            Cell& cell = field.getCell({x, y});
            cell.coordinate.x = jf.at(key).at("x");
            cell.coordinate.y = jf.at(key).at("y");
            cell.state = jf.at(key).at("state");
            cell.value = jf.at(key).at("value");
        }
    }
}

void Deserialization::from_json(AbilityManager& abilityManager, std::string key) {
    const auto& jam = j.at(key);
    abilityManager = AbilityManager();
    abilityManager.popAbility();
    
    for (const auto& jability : jam.at("abilities")) {
       if (jability == "Double Damage") {
           abilityManager.addAbility(new DoubleDamageAbilityCreator());
       }
       else if(jability == "Scanner"){
           abilityManager.addAbility(new ScannerAbilityCreator());
       }
       else if (jability == "Gunblaze") {
           abilityManager.addAbility(new GunblazeAbilityCreator());
       }
    }
}

void Deserialization::from_json(std::map<char, Command>& newCommands) {
    const auto& jc = j.at("commands");
    std::vector<int> values;

    for (const auto& pair : jc.items()) {
        std::string key = pair.key();
        if (key.size() != 1) {
            throw std::invalid_argument("Invalid key.");
        }

        int value = pair.value();
        if (value < 0 || value > 5) {
            throw std::invalid_argument("Incorrect number of commands.");
        }
        values.push_back(value);
        newCommands[key[0]] = static_cast<Command>(value);
    }

    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[i] == values[j]) {
                throw std::invalid_argument("Duplicates in command.");
            }
        }
    }

    if (values.size() != 6) {
        throw std::invalid_argument("Incorrect number of commands.");
    }
}