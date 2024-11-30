#include "../include/Deserialization.hpp"

void Deserialization::from_json(ShipManager& shipManager, std::string key) {
    const auto& jsm = j[key];
    std::vector<int> shipSizes;

    for (const auto& jship : jsm) {
        shipSizes.push_back(jship["length"]);
    }
    shipManager = ShipManager(shipSizes.size(), shipSizes);

    for (size_t i = 0; i < shipSizes.size(); i++) {
        std::string key = "ship" + std::to_string(i);
        Ship& ship = shipManager.getShipByIndex(i);
        if (jsm[key]["horizontal"] == true) {
            ship.setOrientation(Orientation::Horizontal);
        }
        else {
            ship.setOrientation(Orientation::Vertical);
        }

        for (int j = 0; j < shipSizes[i]; j++) {
            Segment* segment = ship.getSegment(j);

            segment->health = jsm[key]["segments"][j]["health"];
            segment->coordinate.x = jsm[key]["segments"][j]["x"];
            segment->coordinate.y = jsm[key]["segments"][j]["y"];
        }
    }
}

void Deserialization::from_json(Field& field, std::string key) {
    const auto& jf = j[key];
    field = Field(jf["rows"], jf["columns"]);

    for (int y = 0; y < field.getRows(); y++) {
        for (int x = 0; x < field.getColumns(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            Cell& cell = field.getCell({x, y});
            cell.coordinate.x = jf[key]["x"];
            cell.coordinate.y = jf[key]["y"];
            cell.state = jf[key]["state"];
            cell.value = jf[key]["value"];
        }
    }
}

void Deserialization::from_json(AbilityManager& abilityManager, std::string key) {
    const auto& jam = j[key];
    abilityManager = AbilityManager();
    abilityManager.popAbility();
    for (const auto& jability : jam["abilities"]) {
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