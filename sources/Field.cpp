#include "../include/Field.hpp"

Field::Field(int rows, int columns) : rows(rows), columns(columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field.push_back(new Cell{{i, j}, CellState::Hidden, CellValue::WaterHidden});
        }
    }
}

void Field::checkCoordinates(Coordinate coordinate) {
    if (coordinate.x < 0 || coordinate.x >= this->columns || coordinate.y < 0 || coordinate.y >= this->rows) {
        throw std::out_of_range("Coordinates are out of range");
    }
}

void Field::initField(ShipManager* fleet) {
    //ДОБАВИТЬ ПРОВЕРКУ НА ОТСУТСВИЕ КОРАБЛЯ НА ЯЧЕЙКЕ
    std::vector<Coordinate> startCoordinates = {{0, 0}, {6, 6}, {5, 0}, {3, 9}, {4, 5}, {0, 5}, {3, 3}, {6, 3}, {8, 3}, {2, 7}};
    int i = 0;
     std::vector<Ship*> ships = fleet->getShips();
    for (auto& ship : ships) {
        if (i == 1 || i == 5) {
            ship->changeOrientation();
        }
        ship->setCoordinate(startCoordinates[i]);
        this->placeShip(ship, startCoordinates[i]);
        ++i;
    }
}

bool Field::placeShip(Ship* ship, Coordinate coordinate) {
    if (coordinate.x < 0 || coordinate.y < 0) {
        return false;
    }
    if (ship->isHorizontal()) {
        if (coordinate.x + ship->getLength() > this->columns) {
            return false;
        }
        if (coordinate.y >= this->rows) {
            return false;
        }
        for (int i = 0; i < ship->getLength(); i++) {
            field[coordinate.y*this->columns + coordinate.x + i]->value = CellValue::ShipPart;
        }
    } else {
        if (coordinate.y + ship->getLength() > this->rows) {
            return false;
        }
        if (coordinate.x >= this->columns) {
            return false;
        }
        for (int i = 0; i < ship->getLength(); i++) {
            
            field[coordinate.y*this->columns + i*this->rows + coordinate.x]->value = CellValue::ShipPart;
        }
    }
    return true;
}

// void Field::placeShipRandomly(Ship* ship) {
//     ///////////////////////////////
// }

void Field::attack(Coordinate coordinate) {
    this->checkCoordinates(coordinate);
    //ДОБАВИТЬ ОБНОВЛЕНИЕ УРОНА ДЛЯ СЕГМЕНТА
    Cell* fieldCell = this->field[this->columns*coordinate.y + coordinate.x];
    switch (fieldCell->value) {
        case CellValue::WaterHidden:
            fieldCell->value = CellValue::WaterRevealed;
            fieldCell->state = CellState::Revealed;
            break;
        case CellValue::ShipPart:
            fieldCell->value = CellValue::Hit;
            break;
        case CellValue::Hit:
            fieldCell->value = CellValue::Destroyed;
            break;
        default:
        std::cout << "Error: Attempt to attack already revealed cell" << std::endl;
            return;
    }
}

void Field::printField() {
    std::cout << std::endl << "-----------------------------------------" << std::endl;
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