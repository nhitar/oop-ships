#include "../include/GameController.hpp"

template <class Input, class Output>
void GameController<Input, Output>::run() {
    Command command = Command::info;
    while (command != Command::quit) {
        switch (command) {
            case Command::info:
                output.printInfo();
                break;

            case Command::attack:
                output.printFields(game.getGameState().getBot().getField(), game.getGameState().getPlayer().getField());
                game.doPlayerAttack();
                game.doBotAttack();
                break;

            case Command::ability:
                if (game.getGameState().getPlayer().getAbilityManager().getCreator(0).isUsingCoordinate()) {
                    output.printAbilityName(game.getGameState().getPlayer().getAbilityManager().getCreator(0).getName());
                    output.printCoordinateNeeded();
                    game.getGameState().setCoordinate(input.processCoordinateInput());
                }
                
                try {
                    game.usePlayerAbility();
                } catch (NoAbilitiesAvailableException& e) {
                    output.printException(e);
                    break;
                } catch (OutOfRangeException& e) {
                    output.printException(e);
                    break;
                }
                std::cout << "Attack" << std::endl;
                game.doPlayerAttack();
                game.doBotAttack();
                break;

            case Command::load:
                std::cout << "Loading the game." << std::endl;
                game.loadGame();
                //output.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
                break;

            case Command::save:
                std::cout << "Saving the game." << std::endl;
                game.saveGame();
                break;

            default:
                std::cout << "Unknown command." << std::endl;
                break;
        }
        if (command != Command::info) {
            output.printInfo();
        }
        command = input.processCommandInput();
    }
}

template class GameController<InputHandler, Painter>;