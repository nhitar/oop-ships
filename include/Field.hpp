#pragma once

#include <vector>

struct Coordinate {
    int x;
    int y;
}

enum class CellState {
    Hidden,
    Revealed
};

struct Cell {
    Coordinate coordinate;
    CellState state; 
};

class Field {
    private:
        int rows;
        int columns;
        std::vector<std::vector<Cell>>field;
    public:
        Field(int rows, int columns);
        //methods
        void initField();
        void placeShip(Coordinate coordinate);
        void placeShipRandomly();
        void attack(Coordinate coordinate);
        void printField();
};