#pragma once

#include "Ship.hpp"
#include "Structs.hpp"

#include "Exceptions/UnableToPlaceShipsException.hpp"
#include "Exceptions/MultipleMissesException.hpp"
#include "Exceptions/OutOfRangeException.hpp"
#include "Exceptions/RevealedCellAttackException.hpp"
#include "Exceptions/ShipPlacementException.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

class Field {
    private:
        int rows;
        int columns;
        std::vector<Cell> field;
    public:
        Field() : rows(0), columns(0) {};
        Field(int rows, int columns);
        Field(const Field& other);
        Field& operator=(const Field& other);
        Field(Field&& other);
        Field& operator=(Field&& other);

        int getRows() const;
        int getColumns() const;
        Cell& getCell(Coordinate coordinate);
        std::vector<Cell> getField() const;

        bool checkCoordinates(Coordinate coordinate);
        bool checkCoordinatesAround(Coordinate coordinate);
        bool isShipAt(Coordinate coordinate);
        
        bool placeShip(Ship* ship, Coordinate coordinate);
        void placeShipRandomly(Ship* ship);
        
        bool attack(Coordinate coordinate);
        Coordinate attackRandomly();

        void revealCells();
        void revealCoordinatesAround(Ship* ship);
};
