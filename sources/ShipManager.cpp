#include "../include/ShipManager.hpp"

ShipManager::ShipManager() {
    std::vector<int> fleet = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (auto length : fleet) {
        this->ships.push_back(new Ship(length));
    }
}
ShipManager::~ShipManager() {
    for (auto& ship : this->ships) {
        delete ship;
    }
}

std::vector<Ship*> ShipManager::getShips() const {
    return this->ships;
}

void ShipManager::addShip(int length) {
    this->ships.push_back(new Ship(length));
}

void ShipManager::checkHealth(Coordinate coordinate) {
    for (auto& ship : this->ships) {
        std::vector<Segment*> segments = ship->getSegments();
        for (auto& segment : segments) {
            if (segment->coordinate.x == coordinate.x && segment->coordinate.y == coordinate.y) {
                switch(segment->health) {
                    case SegmentHealth::Untouched:
                        std::cout << "Segment is untouched" << std::endl;
                        break;
                    case SegmentHealth::Damaged:
                        std::cout << "Segment is damaged" << std::endl;
                        break;
                    case SegmentHealth::Destroyed:
                        std::cout << "Segment is destroyed" << std::endl; 
                        break;
                }
                return;
            }
        }
    }
    std::cout << "Coordinate is empty" << std::endl;
}

// void ShipManager::setHealth(Coordinate coordinate) {
//     coordinate.x++;
// }

void ShipManager::printShips() const{
    for (auto& ship : this->ships) {
        ship->printStatus();
    }
}