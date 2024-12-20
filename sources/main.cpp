#include "../include/Game.hpp"
#include "../include/GameController.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Setup.hpp"

int main() {
    Painter painter = Painter();
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

    ShipManager enemyShips = ShipManager(shipSizes.size(), shipSizes);
    ShipManager selfShips = ShipManager(shipSizes.size(), shipSizes);
    
    try {
        for (size_t i = 0; i < shipSizes.size(); i++) {
            selfField.placeShipRandomly(&selfShips.getShipByIndex(i));
            enemyField.placeShipRandomly(&enemyShips.getShipByIndex(i));
        }
    }
    catch (UnableToPlaceShipsException& e) {
        painter.printException(e);
        return 0;
    }

    selfField.revealCells();
    painter.printFields(selfField, enemyField);
    
    AbilityManager abilityManager;
    Player player = Player(enemyShips, enemyField, abilityManager);
    Bot bot = Bot(selfShips, selfField);
    GameState gameState = GameState(player, bot);
    Game game = Game(player, bot, gameState, painter);

    InputHandler inputHandler = InputHandler();
    Setup setup = Setup(inputHandler);
    try {
        setup.deserializeSetup();
    } catch (std::exception& e) {
        painter.printException(e);
    }

    OutputObserver<Painter>* outputObserver = new OutputObserver<Painter>(painter, gameState);
    game.addObserver(outputObserver);

    GameController<InputHandler, Painter> gameController = GameController<InputHandler, Painter>(game, inputHandler, painter);
    gameController.run();
    return 0;
}