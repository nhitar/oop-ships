#include "../include/GameState.hpp"

void GameState::saveGame(const std::string& file) {
    nlohmann::json j;
    Serialization seri(j);

    seri.to_json(player.getShipManager(), "playerShipManager");
    seri.to_json(player.getField(), "playerField");
    seri.to_json(player.getAbilityManager(), "playerAbilityManager");
    seri.to_json(bot.getShipManager(), "botShipManager");
    seri.to_json(bot.getField(), "botField");

    std::string jsonString = j.dump(4);

    std::ofstream outputFile(file);
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
        std::cout << "JSON data successfully written to " << file << std::endl;
    } else {
        std::cerr << "Unable to open file " << file << std::endl;
    }
}

void GameState::loadGame(const std::string& file) {

}