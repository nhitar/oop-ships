#include "../include/InputHandler.hpp"


InputHandler::InputHandler() {
    this->commands = {
        {'i', Command::info},
        {'a', Command::attack},
        {'b', Command::ability},
        {'l', Command::load},
        {'s', Command::save},
        {'q', Command::quit}
    };
}

void InputHandler::setCommands(std::map <char, Command> newCommands) {
    this->commands = newCommands;
} 

Command InputHandler::processCommandInput() {
    std::string line;
    std::cin >> line;
    if (line.size() == 1 && this->commands.find(line[0]) != this->commands.end()) {
        return this->commands[line[0]];
    }
    return Command::info;
}

Coordinate InputHandler::processCoordinateInput() {
    int x, y;
    while (true) {
        std::cin >> x >> y;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    return Coordinate{x, y};
}