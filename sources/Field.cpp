#include "../include/Field.hpp"

Field::Field(int rows, int columns) : rows(rows), columns(columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field.push_back(new Cell{{i, j}, CellState::Hidden, CellValue::WaterHidden});
        }
    }
}

// void Field::initField() {
//     for (int y = 0; y < this->rows; y++) {
//         for (int x = 0; x < this->columns; x++) {
//             field[y*this->rows + x]->coordinate = {x, y};
//             field[y*this->rows + x]->state = CellState::Hidden;
//             field[y*this->rows + x]->value = CellValue::WaterHidden;
//         }
//     }
// }

bool placeShip(Ship ship, Coordinate coordinate) {
    
    return true;
}

void placeShipRandomly(Ship ship) {
    ///////////////////////////////
}

void attack(Coordinate coordinate) {
    ////////////////////////////////
}

void Field::printField() {
    for (int y = 0; y < this->rows; y++) {
        std::cout << "| ";
        for (int x = 0; x < this->columns; x++) {
            switch (field[y*this->rows + x]->value) {
                case CellValue::ShipPart:
                    std::cout << "S";
                    break;
                case CellValue::Hit:
                    std::cout << "X";
                    break;
                case CellValue::Destroyed:
                    std::cout << "#";
                    break;
                case CellValue::WaterHidden:
                    std::cout << "~";
                    break;
                case CellValue::WaterRevealed:
                    std::cout << ".";
                    break;
            }
            std::cout << " | ";
        }
        std::cout << std::endl << "-----------------------------------------" << std::endl;
    }
}