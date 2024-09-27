#pragma once

#include <iostream>
#include <vector>
#include "Ship.hpp"
#include "Structs.hpp"

class Field {
    private:
        int rows;
        int columns;
        std::vector<Cell*>field;
    public:
        Field(int rows, int columns);
        //methods
        // void initField();
        bool placeShip(Ship ship, Coordinate coordinate);
        void placeShipRandomly(Ship ship);
        void attack(Coordinate coordinate);
        void printField();
};