#include "../include/Field.hpp"


Field::Field(int rows, int columns) : rows(rows), columns(columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field.push_back(Cell{{i, j}, CellState::Hidden, CellValue::WaterHidden});
        }
    }
}

// КОПИРУЮЩИЙ КОНСТРУКТОР
Field::Field(const Field& other) : rows(other.rows), columns(other.columns), field(other.field) {}

// КОПИРУЮЩИЙ ОПЕРАТОР ПРИСВАИВАНИЯ
Field& Field::operator=(const Field& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        field = other.field;
    }
    return *this;
}

// ПЕРЕМЕЩАЮЩИЙ КОНСТРУКТОР
Field::Field(Field&& other) : rows(other.rows), columns(other.columns), field(std::move(other.field)){
    other.rows = 0;
    other.columns = 0;
    other.field.clear();
}

// ПЕРЕМЕЩАЮЩИЙ ОПЕРАТОР ПРИСВАИВАНИЯ
Field& Field::operator=(Field&& other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        field = std::move(other.field);
        other.rows = 0;
        other.columns = 0;
    }
    return *this;
}

int Field::getRows() const {
    return this->rows;
}

int Field::getColumns() const {
    return this->columns;
}

Cell& Field::getCell(Coordinate coordinate) {
    return this->field[coordinate.y * this->columns + coordinate.x];
}

std::vector<Cell> Field::getField() const {
    return this->field;
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

bool Field::isShipAt(Coordinate coordinate) {
    Cell cell = this->field[this->columns*coordinate.y + coordinate.x];
    return (cell.value == CellValue::ShipPart || cell.value == CellValue::Hit || cell.value == CellValue::Destroyed);
}

bool Field::placeShip(Ship* ship, Coordinate coordinate) {
    if (coordinate.x < 0 || coordinate.x < 0) {
        return false;
    }
    // Horizontally
    if (ship->isHorizontal()) {
        if (coordinate.x + ship->getLength() > this->columns) {
            return false;
        }
        if (coordinate.y >= this->rows) {
            return false;
        }

        for (int i = 0; i < ship->getLength(); i++) {
            if (checkCoordinatesAround({coordinate.x + i, coordinate.y})) {
                throw ShipPlacementException();
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
        return true;
    }
    // Vertically
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
    return true;
}

void Field::placeShipRandomly(Ship* ship) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, columns - 1);
    std::uniform_int_distribution<> disY(0, rows - 1);
    std::uniform_int_distribution<> disOrientation(0, 1);

    int j = 0;
    while (true) {
        int randomX = disX(gen);
        int randomY = disY(gen);
        int randOrientation = disOrientation(gen);

        if (randOrientation == 1) {
            ship->changeOrientation();
        }
        try {
            if (this->placeShip(ship, {randomX, randomY})) {
                ship->setCoordinate({randomX, randomY});
                return;
            }
        }
        catch (ShipPlacementException& e) {
            j++;
            if (j >= 30) {
                throw UnableToPlaceShipsException();
            }
            continue;
        }
    }
}

void Field::initField(std::vector<Ship*> fleet) {
    for (auto& ship : fleet) {
        this->placeShipRandomly(ship);
    }
}

bool Field::attack(Coordinate coordinate) {
    if (this->checkCoordinates(coordinate)) {
        throw OutOfRangeException();
    }
    
    Cell& fieldCell = this->field[this->columns*coordinate.y + coordinate.x];
    if (fieldCell.segment) {
        fieldCell.segment->handleDamage();
    }
    fieldCell.state = CellState::Revealed;
    switch (fieldCell.value) {
        case CellValue::WaterHidden:
            fieldCell.value = CellValue::WaterRevealed;
            break;

        case CellValue::ShipPart:
            fieldCell.value = CellValue::Hit;
            break;
        
        case CellValue::Hit:
            fieldCell.value = CellValue::Destroyed;
            break;
        
        default:
            throw RevealedCellAttackException();
            break;
    }
    return true;
}

Coordinate Field::attackRandomly() {
    std::random_device rd;
    std::uniform_int_distribution<> disX(0, columns - 1);
    std::uniform_int_distribution<> disY(0, rows - 1);
    std::mt19937 gen(rd());
    
    int j = 0;
    while(true) {
        int randomX = disX(gen);
        int randomY = disY(gen);
        
        try {
            if (!this->checkCoordinates({randomX, randomY}) && this->attack({randomX, randomY})) {
                return {randomX, randomY};
            }
        }
        catch (RevealedCellAttackException& e) {
            j++;
            if (j > 100000) {
                throw MultipleMissesException();
            }
            continue;
        }
    }
}

void Field::revealCells() {
    for (auto& cell : this->field) {
        cell.state = CellState::Revealed;
    }
}

void Field::revealCoordinatesAround(Ship* ship) {
    for (auto& segment : ship->getSegments()) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (!checkCoordinates({segment->coordinate.x + i, segment->coordinate.y + j})) {
                    Cell& fieldCell = this->field[this->columns*(segment->coordinate.y + j) + segment->coordinate.x + i];
                    if (fieldCell.value != CellValue::WaterHidden) {
                        continue;
                    }
                    fieldCell.state = CellState::Revealed;
                    fieldCell.value = CellValue::WaterRevealed;
                }
            }
        }
    }
}