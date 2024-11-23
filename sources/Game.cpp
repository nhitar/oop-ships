#include "../include/Game.hpp"

void Game::playRound() {
    Painter& painter = Painter::instance();
    while (true) {
        try {
            player.useAbility();
        }
        catch (NoAbilitiesAvailableException& e) {
            painter.printException(e);
            continue;
        }
        catch (OutOfRangeException& e) {
            painter.printException(e);
            continue;
        }
        painter.printFields(this->bot.getField(), this->player.getField());

        if (player.doAttack()) {
            std::cout << "You win!" << std::endl;
            this->isPlayerWin = true;
            return;
        }

        if (bot.doAttack()) {
            std::cout << "You lose!" << std::endl;
            return;
        }

        painter.printFields(this->bot.getField(), this->player.getField());
    }
}


// переделать?
void Game::resetBot() {
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    newField.initField(newShips.getShips());
    Player newPlayer = Player(newShips, newField, player.getAbilityManager());
    this->player = newPlayer;
}

// переделать?
void Game::resetGame() {
    resetBot();
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Field newField = Field(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    newField.initField(newShips.getShips());
    newField.revealCells();
    Bot newBot = Bot(newShips, newField);
    this->bot = newBot;

}

void Game::startGame() {
    Painter& painter = Painter::instance();
    while (true) {
        playRound();
        
        if (this->isPlayerWin) {
            resetBot();
            this->isPlayerWin = false;
        } else {
            resetGame(); 
        }
        
        painter.printFields(bot.getField(), player.getField());
    }
}