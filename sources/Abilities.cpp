#include "../include/Abilities.hpp"

DoubleDamage::DoubleDamage(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {}

Scanner::Scanner(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {}

Gunblaze::Gunblaze(Field& field) : field(field) {}

void DoubleDamage::implementAbility() {
    this->field.attack(this->coordinate);
    this->field.attack(this->coordinate);
}

void Scanner::implementAbility() {
    for (int y = 0; y <= 1; y++) {
        for (int x = 0; x <= 1; x++) {
            if (field.checkCoordinates({coordinate.x+x, coordinate.y+y})) {
                throw std::invalid_argument("Coordinates");
            }
            Cell& fieldCell = field.getField()[field.getColumns()*(coordinate.y+y) + coordinate.x + x];
            if (fieldCell.segment != nullptr) {
                std::cout << "Корабль найден" << std::endl;
                return;
            }
        }
    }
    
    for (int y = 0; y <= 1; y++) {
        for (int x = 0; x <= 1; x++) {
            Cell& fieldCell = field.getCell({coordinate.x+x, coordinate.y+y});
            fieldCell.state = CellState::Revealed;
            fieldCell.value = CellValue::WaterRevealed;
        }
    }
    std::cout << "Корабль не найден" << std::endl;
}

void Gunblaze::implementAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, field.getColumns() - 1);
    std::uniform_int_distribution<> disY(0, field.getRows() - 1);
    
    int j = 0;
    while (true) {
        int randomX = disX(gen);
        int randomY = disY(gen);
        Cell& fieldCell = field.getCell({randomX, randomY});
        if (fieldCell.segment != nullptr && fieldCell.value != CellValue::Destroyed) {
            fieldCell.segment->handleDamage();
            if (fieldCell.value == CellValue::ShipPart) {
                fieldCell.value = CellValue::Hit;
            } else {
                fieldCell.value = CellValue::Destroyed;
            }
            return;
        }
        j++;

        if (j > 1000) {
            std::cout << "Error: Unable to attack randomly" << std::endl;
            return;
        }
    }
}