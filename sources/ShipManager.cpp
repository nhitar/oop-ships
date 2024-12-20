#include "../include/ShipManager.hpp"

ShipManager::ShipManager(int shipCount, std::vector<int> shipSizes) : shipCount(shipCount), shipsAlive(shipCount) {
    for (auto length : shipSizes) {
        this->ships.push_back(Ship(length));
    }
}

Ship& ShipManager::getShipByIndex(int index) {
    return this->ships[index];
}

Ship* ShipManager::getShipByCoordinate(Coordinate coordinate) {
    for (auto& ship : this->ships) {
        for (int i = 0; i < ship.getLength(); i++) {
            if (ship.getSegment(i)->coordinate.x == coordinate.x && ship.getSegment(i)->coordinate.y == coordinate.y) {
                return &ship;
            }
        }
    }
    return nullptr;
}

int ShipManager::getShipCount() const {
    return this->shipCount;
}

int ShipManager::getShipsAlive()const {
    return this->shipsAlive;
}

void ShipManager::setShipsAlive(int count) {
    this->shipsAlive = count;
}

void ShipManager::addShip(int length) {
    this->ships.push_back(Ship(length));
}