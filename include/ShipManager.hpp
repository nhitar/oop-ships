#pragma once

#include "Ship.hpp"

#include <iostream>
#include <vector>

class ShipManager {
    private:
        std::vector<Ship> ships;
        int shipCount;
        int shipsAlive;
    public:
        ShipManager() : ships({}) {};
        ShipManager(int shipCount, std::vector<int> shipSizes);

        Ship& getShipByIndex(int index);
        Ship* getShipByCoordinate(Coordinate coordinate);
        
        int getShipCount() const;

        int getShipsAlive()const;
        void setShipsAlive(int count);

        void addShip(int length);
};
