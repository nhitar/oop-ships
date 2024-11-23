#include "../include/Game.hpp"

void initGame() {
    Painter& painter = Painter::instance();
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
        return;
    }
    ShipManager enemyShips = ShipManager(10, shipSizes);
    ShipManager selfShips = ShipManager(10, shipSizes);
    
    try {
        enemyField.initField(enemyShips.getShips());
        selfField.initField(selfShips.getShips());
    }
    catch (UnableToPlaceShipsException& e) {
        painter.printException(e);
        return;
    }
    selfField.revealCells();
    painter.printFields(selfField, enemyField);
    AbilityManager abilityManager(enemyField);
    Player player = Player(enemyShips, enemyField, abilityManager);
    Bot bot = Bot(selfShips, selfField);
    Game game = Game(player, bot);
    game.startGame();
}

int main() {
    initGame();
    return 0;
}