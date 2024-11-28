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
        painter.printAbilityName(player.getAbilityManager().getCreator().getName());

        try {
            if (player.getAbilityManager().getCreator().isUsingCoordinate()) {
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

    Ship* enemyShip = player.getShipManager().getShip({x, y});
    if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
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
    Ship* selfShip = bot.getShipManager().getShip(coords);
    if (selfShip->getLength() != 0 && selfShip->isDestroyed()) {
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
    newField.initField(newShips.getShips());
    this->player = Player(newShips, newField, player.getAbilityManager());
}

void Game::resetGame() {
    resetBot();
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    newField.initField(newShips.getShips());
    newField.revealCells();
    this->bot = Bot(newShips, newField);
}

void Game::isGameEnded() {
    Painter& painter = Painter::instance();
    if (this->isPlayerWin) {
        resetBot();
        this->isPlayerWin = false;
        painter.printFields(bot.getField(), player.getField());
    }
    if (this->isBotWin) {
        resetGame(); 
        painter.printFields(bot.getField(), player.getField());
    }
}

// void Game::to_json(nlohmann::json& j, const Game& game) {
//     j = nlohmann::json {
//         {"player", game.player},
//         {"bot", game.bot},
//         {"isPlayerWin", game.isPlayerWin}
//     };
// }

// void Game::from_json(nlohmann::json& j, const Game& game) {
//     j.at("player").get_to(game.player);
//     j.at("bot").get_to(game.bot);
//     j.at("isPlayerWin").get_to(game.isPlayerWin);
// }