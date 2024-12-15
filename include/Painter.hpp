#pragma once

#include "AbilityCreator.hpp"
#include "AbilityManager.hpp"
#include "Field.hpp"
#include "Structs.hpp"

#include <fstream>
#include <string>

class Painter {
    public:
        void printLogo(const std::string& filename) const;
        void printException(std::exception& e) const;
        void printString(std::string data) const;
        void printAbilityName(std::string name) const;
        void printAbilityNames(AbilityManager abilityManager) const;
        void printShip(Ship ship) const;
        void printCellValue(Field self, Coordinate coordinate) const;
        void printField(Field self) const;
        void printFields(Field self, Field other) const;
        void printInfo() const;
        void printCoordinateNeeded() const;
};
