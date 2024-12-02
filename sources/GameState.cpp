#include "../include/GameState.hpp"

std::string GameState::getHash(const std::string& data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

Wrapper& operator<<(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    nlohmann::json data;
    Serialization seri(data);
    
    seri.to_json(state.getPlayer().getShipManager(), "playerShipManager");
    seri.to_json(state.getPlayer().getField(), "playerField");
    seri.to_json(state.getPlayer().getAbilityManager(), "playerAbilityManager");
    seri.to_json(state.getBot().getShipManager(), "botShipManager");
    seri.to_json(state.getBot().getField(), "botField");
    data["currentDamage"] = state.getCurrentDamage();
    data["isAbilityUsed"] = state.getIsAbilityUsed();
    
    std::string jsonString = data.dump();

    j["data"] = data;
    j["hashValue"] = state.getHash(jsonString);

    try {
        fileWrapper.write(j);
    }
    catch (UnableToOpenFileException& e){
        std::cerr << e.what() << std::endl;
    }
    
    return fileWrapper;
}

Wrapper& operator>>(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;

    try {
        fileWrapper.read(j);
    }
    catch (UnableToOpenFileException& e) {
        std::cerr << e.what() << std::endl;
        return fileWrapper;
    }


    nlohmann::json data = j.at("data");
    std::string savedHashValue = j.at("hashValue");

    std::string jsonString = data.dump();

    if (savedHashValue != state.getHash(jsonString)) {
        throw HashMismatchException();
    }

    Deserialization deseri(data);
    ShipManager shipManager;
    Field field;
    AbilityManager abilityManager;

    ShipManager enemyShipManager;
    Field enemyField;

    deseri.from_json(shipManager, "playerShipManager");
    deseri.from_json(field, "playerField");
    deseri.from_json(abilityManager, "playerAbilityManager");

    deseri.from_json(enemyShipManager, "botShipManager");
    deseri.from_json(enemyField, "botField");

    state.setCurrentDamage(data.at("currentDamage"));
    state.setIsAbilityUsed(data.at("isAbilityUsed"));

    state.getPlayer().getShipManager() = shipManager;
    state.getPlayer().getField() = field;
    state.getPlayer().getAbilityManager() = abilityManager;

    state.getBot().getShipManager() = enemyShipManager;
    state.getBot().getField() = enemyField;

    state.placeShips(state.getPlayer().getShipManager(), state.getPlayer().getField());
    state.placeShips(state.getBot().getShipManager(), state.getBot().getField());

    return fileWrapper;
}

void GameState::placeShips(ShipManager& shipManager, Field& field) {
    for (int i = 0; i < shipManager.getShipCount(); i++) {
        for (int j = 0; j < shipManager.getShipByIndex(i).getLength(); j++) {
            Coordinate coordinate = shipManager.getShipByIndex(i).getSegment(j)->coordinate;
            auto& cell = field.getCell(coordinate);
            cell.segment = shipManager.getShipByIndex(i).getSegment(j);
        }
    }
}

void GameState::loadGame(const std::string& file) {
    Wrapper fileWrapper(file);
    fileWrapper >> *this;
}

void GameState::saveGame(const std::string& file) {
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::trunc);
    Wrapper fileWrapper(file);
    fileWrapper << *this;

}