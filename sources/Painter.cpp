#include "../include/Painter.hpp"

void Painter::printLogo(const std::string& filename) const {
    std::cout << "\033[1;31m" << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
    std::cout << "\033[1;0m" << std::endl;
}

void Painter::printException(std::exception& e) const {
    std::cerr << "\033[1;31m" <<  "Exception: " << e.what() << "\033[0m" << std::endl;
}

void Painter::printAbilityName(std::string name) const {
    std::cout << name << std::endl;
}

void Painter::printAbilityNames(AbilityManager abilityManager) const {
    for (int i = 0; i < abilityManager.getAbilityCount(); i++) {
        std::cout << abilityManager.getCreator(i).getName() << std::endl;
    }
}

void Painter::printShip(Ship ship) const {
    std::cout << "length: " << ship.getLength()  << std::endl;
    if (ship.isHorizontal()) {
        std::cout << "orientation: horizontal" << std::endl;
    } else {
        std::cout << "orientation: vertical" << std::endl;
    }
    std::cout << "Segments health:" << std::endl;

    for (int i = 0; i < ship.getLength(); i++) {
        switch(ship.getSegment(i)->health) {
            case SegmentHealth::Untouched:
                std::cout << "Untouched" << std::endl;
                break;
            case SegmentHealth::Damaged:
                std::cout << "Damaged" << std::endl;
                break;
            case SegmentHealth::Destroyed:
                std::cout << "Destroyed" << std::endl;
                break;
        }    
    }
}

void Painter::printCellValue(Field self, Coordinate coordinate) const {
    switch (self.getField()[coordinate.y*self.getRows() + coordinate.x].value) {
        case CellValue::ShipPart:
            std::cout << "\033[1;32m" << "S";
            break;
        case CellValue::Hit:
            std::cout << "\033[1;31m" << "X";
            break;
        case CellValue::Destroyed:
            std::cout << "\033[1;30m" << "#";
            break;
        case CellValue::WaterHidden:
            std::cout << "\033[1;34m" << "~";
            break;
        case CellValue::WaterRevealed:
            std::cout << "\033[1;35m" << "*";
            break;
    }
}

void Painter::printField(Field self) const {
    int rows = self.getRows();
    int columns = self.getColumns();
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[30m" << "x---";
    }

    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < rows; y++) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < columns; x++) {
            if (self.getField()[y*rows + x].state == CellState::Revealed) {
                this->printCellValue(self, {x, y});
            } else {
                std::cout << "\033[1;34m" << "~";
            }
            std::cout << "\033[30m" << " | ";
        }
        std::cout << "\033[0m" << y;
        std::cout << std::endl;
        for (int i = 0; i < rows; i++) {
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m";
}

void Painter::printFields(Field self, Field other) const {
    int rows = self.getRows();
    int columns = self.getColumns();
    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << "    ";
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << std::endl;
    for (int i = 0; i < rows * 2; i++) {
        if (i == rows) {
            std::cout << "x   ";
        }
        std::cout << "\033[1;30m" << "x---";
        
    }
    
    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < rows; y++) {
        std::cout << "\033[30m" << "| ";
        int index = 0;
        for (int x = 0; x < columns*2; x++) {
            if (x < columns) {
                if (self.getField()[y*rows + x].state == CellState::Revealed) {
                    this->printCellValue(self, {x, y});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }
            
            if (x == columns) {
                std::cout << "\033[0m" << y;
                std::cout << "\033[30m" << " | ";
            }
            
            if (x >= columns) {
                if (other.getField()[(y-1)*other.getRows() + index].state == CellState::Revealed) {
                    this->printCellValue(other, {index, y-1});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }
            index++;
            std::cout << "\033[30m" << " | ";
        }
        
        std::cout << std::endl;
        for (int i = 0; i < rows*2; i++) {
            if (i == rows) {
                std::cout << "x   ";
            }
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m" << std::endl;
}

void Painter::printInfo() const {
    std::cout << "Push i to print info, a to attack, b to use ability, l to load, s to save, q to quit." << std::endl;
}

void Painter::printCoordinateNeeded() const {
    std::cout << "Input coordinate." << std::endl;
}
