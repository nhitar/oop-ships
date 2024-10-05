#pragma once

#include "Ship.hpp"
#include "Structs.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>

class Field {
    private:
        int rows;
        int columns;
        std::vector<Cell>field;
    public:
        Field(int rows, int columns);
        Field(const Field& other);
        Field& operator=(const Field& other);
        Field(Field&& other);
        Field& operator=(Field&& other);

        //methods
        int getRows() const;
        int getColumns() const;
        std::vector<Cell> getField() const;

        bool checkCoordinates(Coordinate coordinate);
        bool checkCoordinatesAround(Coordinate coordinate);
        bool isShipAt(Coordinate coordinate);
        
        void initField(std::vector<Ship*> ships);
        void revealCells();
        
        bool placeShip(Ship* ship, Coordinate coordinate);
        void placeShipRandomly(Ship* ship);
        
        void attack(Coordinate coordinate);
        Coordinate attackRandomly();

        void revealCoordinatesAround(Ship* ship);
};