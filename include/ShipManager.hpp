#pragma once

#include "Ship.hpp"

#include <iostream>
#include <vector>

class ShipManager {
    private:
        std::vector<Ship> ships;
        int shipCount;
    public:
        ShipManager() : ships({}) {};
        ShipManager(int shipCount, std::vector<int> shipSizes);

        Ship& getShipByIndex(int index);
        
        int getShipCount() const;
        void setShipCount(int count);

        void addShip(int length);
        
        void printShips();
};
