#include "../include/GameState.hpp"
#include <fstream>

Wrapper& operator<<(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    Serialization seri(j);

    seri.to_json(state.player.getShipManager(), "playerShipManager");
    seri.to_json(state.player.getField(), "playerField");
    seri.to_json(state.player.getAbilityManager(), "playerAbilityManager");
    seri.to_json(state.bot.getShipManager(), "botShipManager");
    seri.to_json(state.bot.getField(), "botField");

    fileWrapper.write(j);
    return fileWrapper;
}

Wrapper& operator>>(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    fileWrapper.read(j);

    Deserialization deseri(j);
    deseri.from_json(state.player.getShipManager(), "playerShipManager");
    deseri.from_json(state.player.getField(), "playerField");
    deseri.from_json(state.player.getAbilityManager(), "playerAbilityManager");
    deseri.from_json(state.bot.getShipManager(), "botShipManager");
    deseri.from_json(state.bot.getField(), "botField");

    return fileWrapper;
}

void GameState::saveGame(const std::string& file) {
    Wrapper fileWrapper(file);
    fileWrapper << *this;

}

void GameState::loadGame(const std::string& file) {
    Wrapper fileWrapper(file);
    fileWrapper >> *this;
}