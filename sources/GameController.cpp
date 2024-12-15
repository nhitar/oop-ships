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
                output.printCoordinateNeeded();
                game.getGameState().setCoordinate(input.processCoordinateInput());
                game.doPlayerAttack();
                game.doBotAttack();
                break;

            case Command::ability:
                try {
                    if (game.getGameState().getPlayer().getAbilityManager().getCreator(0).isUsingCoordinate()) {
                        output.printAbilityName(game.getGameState().getPlayer().getAbilityManager().getCreator(0).getName());
                        output.printCoordinateNeeded();
                        game.getGameState().setCoordinate(input.processCoordinateInput());
                    }
                    game.usePlayerAbility();
                } catch (std::exception& e) {
                    output.printException(e);
                    break;
                }
                
                output.printCoordinateNeeded();
                game.getGameState().setCoordinate(input.processCoordinateInput());
                game.doPlayerAttack();
                game.doBotAttack();
                break;

            case Command::load:
                output.printString("Loading the game.");
                game.loadGame();
                break;

            case Command::save:
                output.printString("Saving the game.");
                game.saveGame();
                break;

            default:
                output.printString("Unknown command.");
                break;
        }
        if (command != Command::info) {
            output.printInfo();
        }
        command = input.processCommandInput();
    }
}

template class GameController<InputHandler, Painter>;