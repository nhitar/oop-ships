#include "../include/Game.hpp"

void Game::usePlayerAbility() {
    Painter& painter = Painter::instance();
    int x, y;
    std::cout << "You have " << player.getAbilityManager().getAbilityCount() << " abilities available." << std::endl;
    std::cout << "Use random ability? 'y'" << std::endl;
    std::string result;
    std::cin >> result;

    if (result == "y" || result == "Y") {
        Coordinate coordinate = {-1, -1};
        AbilityParameters ap(player.getField(), player.getShipManager(), coordinate, player.getCurrentDamage());
        player.getAbilityManager().checkIfEmpty();
        painter.printAbilityName(player.getAbilityManager().getCreator(0).getName());

        try {
            if (player.getAbilityManager().getCreator(0).isUsingCoordinate()) {
                std::cout << "Give coordinates for ability." << std::endl;
                std::cin >> x >> y;
                ap.coordinate = {x, y};
            }
            player.getAbilityManager().useAbility(ap);
        }
        catch (RevealedCellAttackException& e) {
            player.getAbilityManager().popAbility();
        }
    }
}

void Game::doPlayerAttack() {
    Painter& painter = Painter::instance();
    int x, y;
    int successAttack = false;
    while (true) {
        try {
            std::cin >> x >> y;
            for (int i = 0; i < player.getCurrentDamage(); i++) {
                player.getField().attack({x, y});
                successAttack = true;
            }

        }
        catch (RevealedCellAttackException& e) {
            if (successAttack) {
                break;
            }
            painter.printException(e);
            continue;
        }
        catch (OutOfRangeException& e) {
            painter.printException(e);
            continue;
        }
        break;
    }
    player.setCurrentDamage(1);

    Ship* enemyShip = player.getShipManager().getShipByCoordinate({x, y});
    if (enemyShip != nullptr && enemyShip->isDestroyed()) {
        player.getField().revealCoordinatesAround(enemyShip);
        player.getShipManager().setShipCount(player.getShipManager().getShipCount() - 1);
        
        std::cout << "Ability added." << std::endl;
        player.getAbilityManager().giveRandomAbility();
    }
    return;
}

void Game::doBotAttack() {
    Painter& painter = Painter::instance();
    Coordinate coords = {-1, -1};
    try {
        coords = bot.getField().attackRandomly();
    }
    catch (MultipleMissesException& e) {
        painter.printException(e);
        return;
    }
    Ship* selfShip = bot.getShipManager().getShipByCoordinate(coords);
    if (selfShip != nullptr && selfShip->isDestroyed()) {
        bot.getField().revealCoordinatesAround(selfShip);
        bot.getShipManager().setShipCount(bot.getShipManager().getShipCount() - 1);
    }
    return;
}

void Game::playTurns() {
    Painter& painter = Painter::instance();
    try {
        usePlayerAbility();
    }
    catch (NoAbilitiesAvailableException& e) {
        painter.printException(e);
        return;
    }
    catch (OutOfRangeException& e) {
        painter.printException(e);
        return;
    }
    painter.printFields(this->bot.getField(), this->player.getField());

    doPlayerAttack();
    if (player.getShipManager().getShipCount() == 0) {
        std::cout << "You win!" << std::endl;
        this->isPlayerWin = true;
        return;
    }

    doBotAttack();
    if (bot.getShipManager().getShipCount() == 0) {
        std::cout << "You lose!" << std::endl;
        this->isBotWin = true;
        return;
    }

    painter.printFields(this->bot.getField(), this->player.getField());
}

void Game::resetBot() {
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    for (size_t i = 0; i < shipSizes.size(); i++) {
        newField.placeShipRandomly(&newShips.getShipByIndex(i));
    }
    this->player = Player(newShips, newField, player.getAbilityManager());
}

void Game::resetGame() {
    resetBot();
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    for (size_t i = 0; i < shipSizes.size(); i++) {
        newField.placeShipRandomly(&newShips.getShipByIndex(i));
    }
    newField.revealCells();
    this->bot = Bot(newShips, newField);
}

bool Game::isGameEnded() {
    Painter& painter = Painter::instance();

    std::cout << "Do you want to continue playing? y/n" << std::endl;
    std::string line;
    std::cin >> line;
    if (line == "n" || line == "N") {
        return true;
    }


    if (this->isPlayerWin) {
        resetBot();
        this->isPlayerWin = false;
        painter.printFields(bot.getField(), player.getField());
    }
    if (this->isBotWin) {
        resetGame(); 
        this->isBotWin = false;
        painter.printFields(bot.getField(), player.getField());
    }
}

void Game::loadGame(const std::string& file) {
    this->gameState.loadGame(file);
}

void Game::saveGame(const std::string& file) {
    this->gameState.saveGame(file);
}   