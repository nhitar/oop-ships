#include "../include/Abilities.hpp"

DoubleDamage::DoubleDamage(int& currentDamage) : currentDamage(currentDamage) {}

Scanner::Scanner(Field& field, Coordinate coordinate) : field(field), coordinate(coordinate) {}

Gunblaze::Gunblaze(Field& field) : field(field) {}

void DoubleDamage::implementAbility() {
    this->currentDamage = 2;
}

void Scanner::implementAbility() {
    for (int y = 0; y <= 1; y++) {
        for (int x = 0; x <= 1; x++) {
            if (field.checkCoordinates({coordinate.x+x, coordinate.y+y})) {
                throw OutOfRangeException();
            }
            Cell& fieldCell = field.getField()[field.getColumns()*(coordinate.y+y) + coordinate.x + x];
            if (fieldCell.segment != nullptr) {
                std::cout << "Ship is in the zone." << std::endl;
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
    std::cout << "Zone is clear." << std::endl;
}

void Gunblaze::implementAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, field.getColumns() - 1);
    std::uniform_int_distribution<> disY(0, field.getRows() - 1);
    
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
    }
}