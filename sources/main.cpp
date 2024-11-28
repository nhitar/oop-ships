#include "../include/Game.hpp"
// #include <nlohmann/json.hpp>
// #include <fstream>
// using json = nlohmann::json;

int main() {
    Painter& painter = Painter::instance();
    painter.printLogo("/home/nhitar/oop-ships/logo.txt");

    Field enemyField = Field(10, 10);
    Field selfField = Field(enemyField);
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    try {
        for (auto& size : shipSizes) {
            if (size < 1 || size > 4) {
                throw InvalidShipSizeException();
            }
        }
    }
    catch (InvalidShipSizeException& e) {
        painter.printException(e);
       return 0;
    }
    ShipManager enemyShips = ShipManager(10, shipSizes);
    ShipManager selfShips = ShipManager(10, shipSizes);
    
    try {
        enemyField.initField(enemyShips.getShips());
        selfField.initField(selfShips.getShips());
    }
    catch (UnableToPlaceShipsException& e) {
        painter.printException(e);
        return 0;
    }
    selfField.revealCells();
    enemyField.revealCells();
    painter.printFields(selfField, enemyField);
    AbilityManager abilityManager;
    Player player = Player(enemyShips, enemyField, abilityManager);
    Bot bot = Bot(selfShips, selfField);
    Game game = Game(player, bot);

    while (true) {
        std::cout << "Push 'p' to play, 'l' to load game, 's' to save game 'q' to quit." << std::endl;
        std::string line;
        std::cin >> line;
        if (line.size() == 1) {
            switch (line[0]) {
                case 'p':
                    game.playTurns();
                    game.isGameEnded();
                    break;

                case 'l':
                    std::cout << "Loading the game." << std::endl;
                    //game.loadGame("saveFile.json");
                    break;

                case 's':
                    std::cout << "Saving the game." << std::endl;
                    //game.saveGame("saveFile.json");
                    break;

                case 'q':
                    std::cout << "Quitting the game." << std::endl;
                    return 0;

                default:
                    std::cout << "Unknown command." << std::endl;
                    break;
            }
            continue;
        }
        std::cout << "Invalid command." << std::endl;
    }

    return 0;
}