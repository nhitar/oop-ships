#include "../include/Player.hpp"

void Player::useAbility() {
    Painter& painter = Painter::instance();
    int x, y;
    std::cout << "You have " << abilityManager.getAbilityCount() << " abilities available." << std::endl;
    std::cout << "Use random ability? 'y'" << std::endl;
    std::string result;
    std::cin >> result;

    if (result == "y" || result == "Y") {
        abilityManager.checkIfEmpty();
        Abilities name = abilityManager.front();
        painter.printAbilityName(name);

        try {
            if (name == Abilities::DoubleDamage || name == Abilities::Scanner) {
                std::cout << "Give coordinates for ability." << std::endl;
                std::cin >> x >> y;
                abilityManager.useAbility({x, y});
            }
            else {
                abilityManager.useAbility();
            }
        }
        catch (RevealedCellAttackException& e) {
            abilityManager.popAbility();
        }
        
        if (name == Abilities::DoubleDamage) {
            Ship* enemyShip = shipManager.getShip({x, y});
            if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
                field.revealCoordinatesAround(enemyShip);
                shipManager.setShipCount(shipManager.getShipCount() - 1);
                
                std::cout << "Ability added." << std::endl;
                abilityManager.giveRandomAbility();
            }
        }
    }
}

bool Player::doAttack() {
    Painter& painter = Painter::instance();
    int x, y;

    while (true) {
        try {
            std::cin >> x >> y;
            field.attack({x, y});
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
    
    Ship* enemyShip = shipManager.getShip({x, y});
    if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
        field.revealCoordinatesAround(enemyShip);
        shipManager.setShipCount(shipManager.getShipCount() - 1);
        
        std::cout << "Ability added." << std::endl;
        abilityManager.giveRandomAbility();

        if (shipManager.getShipCount() == 0) {
            return true;
        }
    }
    return false;
}

bool Bot::doAttack() {
    Painter& painter = Painter::instance();
    Coordinate coords = {-1, -1};
    try {
        coords = field.attackRandomly();
    }
    catch (MultipleMissesException& e) {
        painter.printException(e);
        return false;
    }
    Ship* selfShip = shipManager.getShip(coords);
    if (selfShip->getLength() != 0 && selfShip->isDestroyed()) {
        field.revealCoordinatesAround(selfShip);
        shipManager.setShipCount(shipManager.getShipCount() - 1);
        if (shipManager.getShipCount() == 0) {
            return true;
        }
    }
    return false;
}