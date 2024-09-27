#pragma once

#include <iostream>
#include <vector>
#include "Ship.hpp"

class ShipManager {
    private:
        std::vector<Ship*>ships;
    public:
        ShipManager();
        ~ShipManager();
        //methods
        std::vector<Ship*> getShips() const;

        void addShip(int length);
        
        void checkHealth(Coordinate coordinate);
        void setHealth(Coordinate coordinate);
        
        void printShips() const;
};

