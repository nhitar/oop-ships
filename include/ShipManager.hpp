#pragma once

#include "Ship.hpp"
#include <iostream>
#include <vector>

class ShipManager {
    private:
        std::vector<Ship*>ships;
        int shipCount;
    public:
        ShipManager(int shipCount, std::vector<int> shipSizes);
        ~ShipManager();
        // methods
        Ship* getShip(Coordinate coordinate) const;
        std::vector<Ship*> getShips() const;
        
        int getShipCount() const;
        void setShipCount(int count);

        void addShip(int length);
        
        void printShips() const;
};