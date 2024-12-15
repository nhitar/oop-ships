#pragma once

#include "Game.hpp"
#include "InputHandler.hpp"

template <class Input, class Output>
class GameController {
    private:
        Game& game;
        Input& input;
        Output& output;
    public:
        GameController(Game& game, Input& input, Output& output) 
            : game(game), input(input), output(output) {};

        void run() {
            Command command = Command::info;
            while (command != Command::quit) {
                switch (command) {
                    case Command::info:
                        output.printInfo();
                        break;

                    case Command::attack:
                        output.printFields(game.getGameState().getBot().getField(), game.getGameState().getPlayer().getField());
                        attackCycle();
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
                        
                        attackCycle();
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

        void attackCycle() {
            output.printCoordinateNeeded();
            while (true) {
                try {
                    game.getGameState().setCoordinate(input.processCoordinateInput());
                    game.doPlayerAttack();
                }
                catch (RevealedCellAttackException& e) {
                    output.printException(e);
                    continue;
                }
                catch (OutOfRangeException& e) {
                    output.printException(e);
                    continue;
                }
                break;
            }
            game.doBotAttack();
        }
};