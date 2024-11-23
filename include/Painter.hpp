#pragma once

#include "AbilityCreator.hpp"
#include "Field.hpp"
#include "Structs.hpp"

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
        void printException(std::exception& e) const;
        void printAbilityName(Abilities name) const;
        void printCellValue(Field self, Coordinate coordinate) const;
        void printField(Field self) const;
        void printFields(Field self, Field other) const;
};
