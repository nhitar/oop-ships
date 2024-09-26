#pragma once

#include <vector>
#include "Ship.hpp"

class ShipManager {
    private:
        std::vector<Ship>ships;
    public:
        ShipManager();
        //methods
        Ship getShips() const;
        std::vector<Ship> getShips() const;

        void addShip(int length, Orientation orientation);
        void createAllShips();
        
        void checkHealth(Coordinate coordinate);
        void setHealth(Coordinate coordinate);
        
        void printShips();
};

