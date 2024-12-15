#include "../include/GameController.hpp"

template <class Input, class Output>
void GameController<Input, Output>::run() {
    Command command = Command::info;
    while (command != Command::quit) {
        switch (command) {
            case Command::info:
                std::cout << "Push i to print info, a to attack, b to use ability, l to load, s to save, q to quit." << std::endl;
                break;

            case Command::attack:
                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                game.doPlayerAttack();
                game.doBotAttack();
                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                break;

            case Command::ability:
                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                try {
                    game.usePlayerAbility();
                } catch (NoAbilitiesAvailableException& e) {
                    outputHandler.printException(e);
                    break;
                } catch (OutOfRangeException& e) {
                    outputHandler.printException(e);
                    break;
                }

                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                std::cout << "Player attacking." << std::endl;
                game.doPlayerAttack();
                game.doBotAttack();
                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                break;

            case Command::load:
                std::cout << "Loading the game." << std::endl;
                game.loadGame();
                outputHandler.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                break;

            case Command::save:
                std::cout << "Saving the game." << std::endl;
                game.saveGame();
                break;

            default:
                std::cout << "Unknown command." << std::endl;
                break;
        }
        std::cout<< "Give command." << std::endl;
        command = inputHandler.processCommandInput();
    }
}

template class GameController<InputHandler, Painter>;