#include "../include/InputHandler.hpp"


InputHandler::InputHandler() {
    this->commands = {
        {'0', Command::info},
        {'1', Command::attack},
        {'2', Command::ability},
        {'3', Command::load},
        {'4', Command::save},
        {'5', Command::quit}
    };
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