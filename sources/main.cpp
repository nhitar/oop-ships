#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"

int main() {
    Painter painter;
    Field enemyField = Field(10, 10);
    Field selfField = Field(enemyField);

    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager* enemyShips = new ShipManager(10, shipSizes);
    ShipManager* selfShips = new ShipManager(10, shipSizes);

    enemyField.initField(enemyShips->getShips());
    selfField.initField(selfShips->getShips());
    selfField.revealCells();

    painter.printFields(selfField, enemyField);
    while (true) {
        int x, y;
        std::cin >> x >> y;
        while (!enemyField.attack({x, y})) {
            std::cin >> x >> y;
        }

        Ship* enemyShip = enemyShips->getShip({x, y});
        if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
            enemyField.revealCoordinatesAround(enemyShip);
            enemyShips->setShipCount(enemyShips->getShipCount() - 1);
            if (enemyShips->getShipCount() == 0) {
                std::cout << "You win!" << std::endl;
                break;
            }
        }

        Coordinate coords = selfField.attackRandomly();
        Ship* selfShip = selfShips->getShip(coords);
        if (selfShip->getLength() != 0 && selfShip->isDestroyed()) {
            selfField.revealCoordinatesAround(selfShip);
            selfShips->setShipCount(selfShips->getShipCount() - 1);
            if (selfShips->getShipCount() == 0) {
                std::cout << "You lose!" << std::endl;
                break;
            }
        }

        painter.printFields(selfField, enemyField);
    }
    return 0;
}