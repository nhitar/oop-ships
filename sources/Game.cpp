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
    if (player.getShipManager().getShipsAlive() == 0) {
        std::cout << "You win!" << std::endl;
        this->isPlayerWin = true;
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
        this->isBotWin = true;
    }
    return;
}

void Game::startGame() {
    std::string answer;
    const std::string file = "/home/nhitar/oop-ships/savefile.json";
    while (!this->gameEnder) {
        std::cout << "Push 'p' to play, 'l' to load game, 's' to save game, 'q' to quit." << std::endl;
        std::string line;
        std::cin >> line;
        if (line.size() == 1) {
            switch (line[0]) {
                case 'p':
                    painter.printFields(bot.getField(), player.getField());
                    if (!this->gameState.getIsAbilityUsed()) {
                        try {
                            usePlayerAbility();
                        } catch (NoAbilitiesAvailableException& e) {
                            painter.printException(e);
                            break;
                        }
                        catch (OutOfRangeException& e) {
                            painter.printException(e);
                            break;
                        }
                        
                        std::cout << "Do you want to quit/load/save the game? y/n" << std::endl;
                        std::cin >> answer;
                        if (answer == "y" || answer == "Y") { 
                            break;
                        }
                    }
                    painter.printFields(bot.getField(), player.getField());
                    doPlayerAttack();
                    doBotAttack();

                    for (int i = 0; i < 10; i++) 
                        painter.printShip(player.getShipManager().getShipByIndex(i));

                    painter.printFields(bot.getField(), player.getField());
                    this->isGameEnded();
                    break;

                case 'l':
                    std::cout << "Loading the game." << std::endl;
                    this->loadGame(file);
                    painter.printFields(bot.getField(), player.getField());
                    break;

                case 's':
                    std::cout << "Saving the game." << std::endl;
                    this->saveGame(file);
                    break;

                case 'q':
                    std::cout << "Quitting the game." << std::endl;
                    this->gameEnder = true;
                    break;

                default:
                    std::cout << "Unknown command." << std::endl;
                    break;
            }
            continue;
        }
        std::cout << "Invalid command." << std::endl;
    }
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

void Game::isGameEnded() {
    if (!this->isPlayerWin && !this->isBotWin) {
        this->gameEnder = false;
        return;
    }

    std::cout << "Do you want to continue playing? y/n" << std::endl;
    std::string line;
    std::cin >> line;
    if (line == "n" || line == "N") {
        this->gameEnder = true;
        return;
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
    try {
        this->gameState.loadGame(file);
    } catch (nlohmann::json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
       return;
    }
}

void Game::saveGame(const std::string& file) {
    this->gameState.saveGame(file);
}   