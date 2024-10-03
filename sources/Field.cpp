#include "../include/Field.hpp"

Field::Field(int rows, int columns) : rows(rows), columns(columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field.push_back(Cell{{i, j}, CellState::Hidden, CellValue::WaterHidden});
        }
    }
}

bool Field::checkCoordinates(Coordinate coordinate) {
    if (coordinate.x < 0 || coordinate.x >= this->columns || coordinate.y < 0 || coordinate.y >= this->rows) {
        return true;
    }
    return false;
}

bool Field::checkCoordinatesAround(Coordinate coordinate) {
	if (checkCoordinates(coordinate)) {
        return true;
    }
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (!checkCoordinates({coordinate.x + i, coordinate.y + j})) {
                if (field[coordinate.x + i + (coordinate.y + j) * this->columns].segment != nullptr) {
                    return true;
                }
            }
        }
    }

	return false;
}

void Field::initField(std::vector<Ship*> fleet) {
    for (auto& ship : fleet) {
        this->placeShipRandomly(ship);
    }
}

bool Field::isShipAt(Coordinate coordinate) {
    Cell cell = this->field[this->columns*coordinate.y + coordinate.x];
    return (cell.value == CellValue::ShipPart || cell.value == CellValue::Hit || cell.value == CellValue::Destroyed);
}

bool Field::placeShip(Ship* ship, Coordinate coordinate) {
    if (coordinate.x < 0 || coordinate.x < 0) {
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
            if (checkCoordinatesAround({coordinate.x + i, coordinate.y})) {
                return false;
            }
            if (this->isShipAt({coordinate.x + i, coordinate.y})) {
                return false;
            }
        }
        for (int i = 0; i < ship->getLength(); i++) {
            ship->getSegments()[i]->coordinate = Coordinate{coordinate.x, coordinate.y + i};
            field[coordinate.y*this->columns + coordinate.x + i].segment = ship->getSegments()[i];
            field[coordinate.y*this->columns + coordinate.x + i].value = CellValue::ShipPart;
        }
    } else {
        if (coordinate.y + ship->getLength() > this->rows) {
            return false;
        }
        if (coordinate.x >= this->columns) {
            return false;
        }

        for (int i = 0; i < ship->getLength(); i++) {
            if (checkCoordinatesAround({coordinate.x, coordinate.y + i})) {
                return false;
            }
            if (this->isShipAt({coordinate.x, coordinate.y + i})) {
                return false;
            }
        }
        for (int i = 0; i < ship->getLength(); i++) {
            ship->getSegments()[i]->coordinate = Coordinate{coordinate.x + i, coordinate.y};
            field[(coordinate.y + i)*this->columns + coordinate.x].segment = ship->getSegments()[i];
            field[(coordinate.y + i)*this->columns + coordinate.x].value = CellValue::ShipPart;
        }
    }
    return true;
}

void Field::placeShipRandomly(Ship* ship) {
    std::srand(static_cast<unsigned int>(std::time(0)));
    int randomX, randomY, randOrientation;
    int j = 0;
    while(true) {
        randomX = std::rand() % this->columns;
        randomY = std::rand() % this->rows;
        randOrientation = std::rand() % 2;

        if (randOrientation == 1) {
            ship->changeOrientation();
        }
        
        if (this->placeShip(ship, {randomX, randomY})) {
            ship->setCoordinate({randomX, randomY});
            return;
        } else {
            j++;
        }

        if (j > 100) {
            std::cout << "Error: Unable to place ship randomly" << std::endl;
            return;
        }
    }
}

void Field::attack(Coordinate coordinate) {
    if (this->checkCoordinates(coordinate)) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return;
    }
    
    Cell& fieldCell = this->field[this->columns*coordinate.y + coordinate.x];
    fieldCell.state = CellState::Revealed;
    switch (fieldCell.value) {
        case CellValue::WaterHidden:
            fieldCell.value = CellValue::WaterRevealed;
            break;
        case CellValue::ShipPart:
            fieldCell.segment->health = SegmentHealth::Damaged;
            fieldCell.value = CellValue::Hit;
            break;
        case CellValue::Hit:
            fieldCell.segment->health = SegmentHealth::Destroyed;
            fieldCell.value = CellValue::Destroyed;
            break;
        default:
            std::cout << "Error: Attempt to attack already revealed cell" << std::endl;
            break;
    }
}

void Field::printField() {
    for (int i = 0; i < this->rows; i++) {
        std::cout << "\033[30m" << "x---";
    }
    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < this->rows; y++) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < this->columns; x++) {
            if (field[y*this->rows + x].state == CellState::Revealed) {
                switch (field[y*this->rows + x].value) {
                    case CellValue::ShipPart:
                        std::cout << "\033[32m" << "S";
                        break;
                    case CellValue::Hit:
                        std::cout << "\033[1;31m" << "X";
                        break;
                    case CellValue::Destroyed:
                        std::cout << "\033[30m" << "#";
                        break;
                    case CellValue::WaterHidden:
                        std::cout << "\033[34m" << "~";
                        break;
                    case CellValue::WaterRevealed:
                        std::cout << "\033[1;35m" << "*";
                        break;
                }
                
            } else {
                std::cout << "\033[1;34m" << "~";
            }
            std::cout << "\033[30m" << " | ";
        }
        std::cout << std::endl;
        for (int i = 0; i < this->rows; i++) {
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m";
}