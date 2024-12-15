#include "../include/Game.hpp"

void Game::usePlayerAbility() {
    int x, y;
    std::cout << "You have " << player.getAbilityManager().getAbilityCount() << " abilities available." << std::endl;
    std::cout << "Use random ability? 'y'" << std::endl;
    std::string result;
    std::cin >> result;

    if (result == "y" || result == "Y") {
        Coordinate coordinate = {-1, -1};
        AbilityParameters ap(player.getField(), player.getShipManager(), coordinate, gameState.getCurrentDamage());
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
    this->gameState.setIsAbilityUsed(true);
}

void Game::doPlayerAttack() {
    int x, y;
    int successAttack = false;
    while (true) {
        try {
            std::cin >> x >> y;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidCoordinateException();
            }
            
            for (int i = 0; i < gameState.getCurrentDamage(); i++) {
                player.getField().attack({x, y});
                successAttack = true;
            }
        }
        catch (InvalidCoordinateException& e) {
            painter.printException(e);
            continue;
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
    this->gameState.setCurrentDamage(1);

    Ship* enemyShip = player.getShipManager().getShipByCoordinate({x, y});
    if (enemyShip != nullptr && enemyShip->isDestroyed()) {
        player.getField().revealCoordinatesAround(enemyShip);
        player.getShipManager().setShipsAlive(player.getShipManager().getShipsAlive() - 1);
        
        std::cout << "Ability added." << std::endl;
        player.getAbilityManager().giveRandomAbility();
    }

    for (const auto& observer : this->observers) {
        observer->turnEnded();
    }

    if (player.getShipManager().getShipsAlive() == 0) {
        std::cout << "You win!" << std::endl;
        for (const auto& observer : this->observers) {
            observer->playerWin();
        }
        this->resetBot();
    }
    this->gameState.setIsAbilityUsed(false);
    return;
}

void Game::doBotAttack() {
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
        bot.getShipManager().setShipsAlive(bot.getShipManager().getShipsAlive() - 1);
    }

    if (bot.getShipManager().getShipsAlive() == 0) {
        std::cout << "You lose!" << std::endl;
        for (const auto& observer : this->observers) {
            observer->botWin();
        }
        this->resetGame();
    }
    return;
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

void Game::addObserver(Observer* observer) {
    this->observers.push_back(observer);
}

void Game::loadGame() {
    try {
        this->gameState.loadGame();
    } catch (nlohmann::json::exception& e) {
        std::cerr << "\033[1;31m" << "Error parsing JSON: " << e.what() << "\033[0m" << std::endl;
        return;
    } catch (HashMismatchException& e) {
        painter.printException(e);
        return;
    }
}

void Game::saveGame() {
    this->gameState.saveGame();
}   