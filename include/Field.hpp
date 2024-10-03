#pragma once

#include "Ship.hpp"
#include "Structs.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Field {
    private:
        int rows;
        int columns;
        std::vector<Cell>field;
    public:
        Field(int rows, int columns);
        //methods
        bool checkCoordinates(Coordinate coordinate);
        bool checkCoordinatesAround(Coordinate coordinate);
        bool isShipAt(Coordinate coordinate);
        
        void initField(std::vector<Ship*> ships);
        
        bool placeShip(Ship* ship, Coordinate coordinate);
        void placeShipRandomly(Ship* ship);
        
        void attack(Coordinate coordinate);

        void printField();
};