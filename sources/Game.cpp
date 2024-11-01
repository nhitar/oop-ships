#include "../include/Game.hpp"

void Game::initGame() {
    Painter painter;
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
    ShipManager* enemyShips = new ShipManager(10, shipSizes);
    ShipManager* selfShips = new ShipManager(10, shipSizes);
    
    try {
        enemyField.initField(enemyShips->getShips());
        selfField.initField(selfShips->getShips());
    }
    catch (UnableToPlaceShipsException& e) {
        painter.printException(e);
        return;
    }
    selfField.revealCells();
    painter.printFields(selfField, enemyField);
    AbilityManager am(enemyField);

    while (true) {
        int x, y;
        std::cout << "You have " << am.getAbilityCount() << " abilities available." << std::endl;
        std::cout << "Use random ability? 'y'" << std::endl;
        std::string result;
        std::cin >> result;

        // Player ability
        if (result == "y" || result == "Y") {
            try {
                am.checkIfEmpty();
            }
            catch (NoAbilitiesAvailableException& e) {
                painter.printException(e);
                continue;
            }
            Abilities name = am.front();
            painter.printAbilityName(name);

            try {
                if (name == Abilities::DoubleDamage || name == Abilities::Scanner) {
                    std::cout << "Give coordinates for ability." << std::endl;
                    std::cin >> x >> y;
                    am.useAbility({x, y});
                }
                else {
                    am.useAbility();
                }
            }
            catch (RevealedCellAttackException& e) {
                am.popAbility();
            }
            catch (OutOfRangeException& e) {
                painter.printException(e);
                continue;
            }
            
            if (name == Abilities::DoubleDamage) {
                Ship* enemyShip = enemyShips->getShip({x, y});
                if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
                    enemyField.revealCoordinatesAround(enemyShip);
                    enemyShips->setShipCount(enemyShips->getShipCount() - 1);
                    
                    std::cout << "Ability added." << std::endl;
                    am.giveRandomAbility();
                }
            }
            painter.printFields(selfField, enemyField);
        }
        
        // Attack
        while (true) {
            try {
                std::cin >> x >> y;
                enemyField.attack({x, y});
            }
            catch (RevealedCellAttackException& e) {
                painter.printException(e);
                continue;
            }
            catch (OutOfRangeException& e) {
                painter.printException(e);
                continue;
            }
            break;
        }
        
        Ship* enemyShip = enemyShips->getShip({x, y});
        if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
            enemyField.revealCoordinatesAround(enemyShip);
            enemyShips->setShipCount(enemyShips->getShipCount() - 1);
            
            std::cout << "Ability added." << std::endl;
            am.giveRandomAbility();

            if (enemyShips->getShipCount() == 0) {
                std::cout << "You win!" << std::endl;
                break;
            }
        }
        
        // Enemy attack
        Coordinate coords = {-1, -1};
        try {
            coords = selfField.attackRandomly();
        }
        catch (MultipleMissesException& e) {
            painter.printException(e);
            continue;
        }
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
}