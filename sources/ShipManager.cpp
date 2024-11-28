#include "../include/ShipManager.hpp"

ShipManager::ShipManager(int shipCount, std::vector<int> shipSizes) : shipCount(shipCount) {
    for (auto length : shipSizes) {
        this->ships.push_back(new Ship(length));
    }
}
ShipManager::~ShipManager() {
    for (auto& ship : this->ships) {
        delete ship;
    }
}

Ship* ShipManager::getShip(Coordinate coordinate) const {
    for (auto& ship : this->ships) {
        for (auto& segment : ship->getSegments()) {
            if (segment->coordinate.x == coordinate.x && segment->coordinate.y == coordinate.y) {
                return ship;
            }
        }
    }
    return new Ship(0);
}

std::vector<Ship*> ShipManager::getShips() const {
    return this->ships;
}

int ShipManager::getShipCount() const {
    return this->shipCount;
}

void ShipManager::setShipCount(int count) {
    this->shipCount = count;
}

void ShipManager::addShip(int length) {
    this->ships.push_back(new Ship(length));
}

void ShipManager::printShips() const{
    for (auto& ship : this->ships) {
        ship->printStatus();
    }
}

// void ShipManager::to_json(nlohmann::json& j, const ShipManager& sm) {
//     j = nlohmann::json {
//         {"ships", sm.ships},
//         {"shipCount", sm.shipCount}
//     };
// }

// void ShipManager::from_json(const nlohmann::json& j, ShipManager& sm) {
//     j.at("ships").get_to(sm.ships);
//     j.at("shipCount").get_to(sm.shipCount);
// }