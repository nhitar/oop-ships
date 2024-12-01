#include "../include/GameState.hpp"

Wrapper& operator<<(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    Serialization seri(j);

    seri.to_json(state.player.getShipManager(), "playerShipManager");
    seri.to_json(state.player.getField(), "playerField");
    seri.to_json(state.player.getAbilityManager(), "playerAbilityManager");
    seri.to_json(state.bot.getShipManager(), "botShipManager");
    seri.to_json(state.bot.getField(), "botField");

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

    Deserialization deseri(j);
    deseri.from_json(state.player.getShipManager(), "playerShipManager");
    deseri.from_json(state.player.getField(), "playerField");
    deseri.from_json(state.player.getAbilityManager(), "playerAbilityManager");
    deseri.from_json(state.bot.getShipManager(), "botShipManager");
    deseri.from_json(state.bot.getField(), "botField");

    state.placeShips(state.player.getShipManager(), state.player.getField());
    state.placeShips(state.bot.getShipManager(), state.bot.getField());

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