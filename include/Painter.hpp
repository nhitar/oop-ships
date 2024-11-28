#pragma once

#include "AbilityCreator.hpp"
#include "Field.hpp"
#include "Structs.hpp"

#include <fstream>
#include <string>

class Painter {
    private:
        Painter(){}
        Painter(const Painter& root) = delete;
        Painter& operator=(const Painter&) = delete;
    public:
        static Painter& instance() {
            static Painter singleton;
            return singleton;
        }
        void printLogo(const std::string& filename) const;
        void printException(std::exception& e) const;
        void printAbilityName(std::string name) const;
        void printCellValue(Field self, Coordinate coordinate) const;
        void printField(Field self) const;
        void printFields(Field self, Field other) const;
};
