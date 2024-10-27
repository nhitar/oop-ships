#include "../include/Ship.hpp"
#include "../include/ShipManager.hpp"
#include "../include/Field.hpp"
#include "../include/Painter.hpp"
#include "../include/Abilities.hpp"
#include "../include/AbilityManager.hpp"

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
    // enemyField.revealCells();
    painter.printFields(selfField, enemyField);
    AbilityManager am(enemyField);
    while (true) {
        int x, y;
        
        if (am.getAbilityCount() > 0) {
            std::cout << am.getAbilityCount() << std::endl;
            std::cout << "Использовать случайную способность? y/n" << std::endl;
            std::string result;
            std::cin >> result;

            if (result == "y" || result == "Y") {
                Abilities name = am.front();
                if (name == Abilities::DoubleDamage) {
                    std::cout << "Double Damage" << std::endl;   
                } else if (name == Abilities::Scanner) {
                    std::cout << "Scanner" << std::endl;
                } else {
                    std::cout << "Gunblaze" << std::endl;
                }
                x = y = 0;
                
                if (name == Abilities::DoubleDamage || name == Abilities::Scanner) {
                    std::cout << "Куда использовать способность?" << std::endl;
                    std::cin >> x >> y;
                    am.useAbility({x, y});
                }
                else {
                    am.useAbility();
                }

                if (name == Abilities::DoubleDamage) {
                    Ship* enemyShip = enemyShips->getShip({x, y});
                    if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
                        enemyField.revealCoordinatesAround(enemyShip);
                        enemyShips->setShipCount(enemyShips->getShipCount() - 1);
                        
                        std::cout << "Получена способность" << std::endl;
                        am.giveRandomAbility();
                    }
                }

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
            am.giveRandomAbility();

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