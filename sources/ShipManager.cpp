#include "../include/ShipManager.hpp"

ShipManager::ShipManager(int shipCount, std::vector<int> shipSizes) : shipCount(shipCount) {
    for (auto length : shipSizes) {
        this->ships.push_back(Ship(length));
    }
}

Ship& ShipManager::getShipByIndex(int index) {
    return this->ships[index];
}

int ShipManager::getShipCount() const {
    return this->shipCount;
}

void ShipManager::setShipCount(int count) {
    this->shipCount = count;
}

void ShipManager::addShip(int length) {
    this->ships.push_back(Ship(length));
}

void ShipManager::printShips() {
    for (auto& ship : this->ships) {
        ship.printStatus();
    }
}