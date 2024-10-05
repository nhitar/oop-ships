#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"

int main() {
    Painter painter;
    Field enemyField = Field(10, 10);
    Field selfField = Field(enemyField);

    ShipManager* enemyShips = new ShipManager;
    ShipManager* selfShips = new ShipManager;

    enemyField.initField(enemyShips->getShips());
    selfField.initField(selfShips->getShips());
    selfField.revealCells();

    painter.printFields(selfField, enemyField);
    while (true) {
        int x, y;
        std::cin >> x >> y;
        enemyField.attack({x, y});

        Ship* enemyShip = enemyShips->getShip({x, y});
        if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
            enemyField.revealCoordinatesAround(enemyShip);
        }

        Coordinate coords = selfField.attackRandomly();
        Ship* selfShip = selfShips->getShip(coords);
        if (selfShip->getLength() != 0 && selfShip->isDestroyed()) {
            selfField.revealCoordinatesAround(selfShip);
        }

        painter.printFields(selfField, enemyField);
    }
    return 0;
}

//TODO:
//Убрать лишние методы
//Улучшить бота, чтобы он добивал корабль
//Сделать конец игры
//Сделать гойду
//
//Сделать отчёт