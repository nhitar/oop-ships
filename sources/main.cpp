#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"
#include "../include/Abilities.hpp"
#include "../include/AbilityManager.hpp"

int main() {
    Painter painter;
    AbilityManager am;
    Field enemyField = Field(10, 10);
    Field selfField = Field(enemyField);

    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager* enemyShips = new ShipManager(10, shipSizes);
    ShipManager* selfShips = new ShipManager(10, shipSizes);

    enemyField.initField(enemyShips->getShips());
    selfField.initField(selfShips->getShips());
    selfField.revealCells();
    // enemyField.revealCells();
    painter.printFields(selfField, enemyField);
    while (true) {
        int x, y;
        
        if (am.getAbilityCount() > 0) {
            std::cout << am.getAbilityCount() << std::endl;
            std::cout << "Использовать случайную способность? y/n" << std::endl;
            std::string result;
            std::cin >> result;

            if (result == "y" || result == "Y") {
                am.setAbilityCount(am.getAbilityCount() - 1);
                std::string name = am.getDeque()->front()->getAbilityName();
                std::cout << name << std::endl;
                x = y = 0;
                
                am.getDeque()->front()->setField(&enemyField);
                if (name == "Double Damage" || name == "Scanner") {
                    std::cout << "Куда использовать способность?" << std::endl;
                    std::cin >> x >> y;
                    am.getDeque()->front()->setCoordinate({x, y});
                }
                am.getDeque()->front()->implementAbility();
                
                if (name == "Double Damage") {
                    Ship* enemyShip = enemyShips->getShip({x, y});
                    if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
                        enemyField.revealCoordinatesAround(enemyShip);
                        enemyShips->setShipCount(enemyShips->getShipCount() - 1);
                        
                        std::cout << "Получена способность" << std::endl;
                        am.addAbility();
                    }
                }

                am.getDeque()->pop_front();
                painter.printFields(selfField, enemyField);
            }
        }

        std::cin >> x >> y;
        while (!enemyField.attack({x, y})) {
            std::cin >> x >> y;
        }
        
        Ship* enemyShip = enemyShips->getShip({x, y});
        if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
            enemyField.revealCoordinatesAround(enemyShip);
            enemyShips->setShipCount(enemyShips->getShipCount() - 1);
            
            std::cout << "Получена способность" << std::endl;
            am.addAbility();

            if (enemyShips->getShipCount() == 0) {
                std::cout << "You win!" << std::endl;
                break;
            }
        }
        //enemyShips->printShips();

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