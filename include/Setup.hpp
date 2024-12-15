#pragma once

#include "InputHandler.hpp"
#include "Deserialization.hpp"
#include "Wrapper.hpp"

class Setup {
    private:
        InputHandler& inputHandler;
    public:
        Setup(InputHandler& inputHandler) : inputHandler(inputHandler) {};
        void deserializeSetup() {
            nlohmann::json j;
            Wrapper fileWrapper = Wrapper("/home/nhitar/oop-ships/setup.json");
            std::map<char, Command> newCommands;
            fileWrapper.read(j);
            Deserialization(j).from_json(newCommands);
            inputHandler.setCommands(newCommands);
        }
};