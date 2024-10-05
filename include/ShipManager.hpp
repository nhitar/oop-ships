#pragma once

#include "Ship.hpp"
#include <iostream>
#include <vector>

class ShipManager {
    private:
        std::vector<Ship*>ships;
    public:
        ShipManager();
        ~ShipManager();
        //methods
        std::vector<Ship*> getShips() const;
        Ship* getShip(Coordinate coordinate) const;

        void addShip(int length);

        //УДАЛИТЬ
        // void checkHealth(Coordinate coordinate);
        // void setHealth(Coordinate coordinate);
        
        void printShips() const;
};

