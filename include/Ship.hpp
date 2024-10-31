#pragma once

#include "Structs.hpp"

#include <iostream>
#include <vector>

class Ship {
    private:
        int length;
        Orientation orientation;
        std::vector<Segment*> segments;
    public:
        Ship(int length);
        ~Ship();
        // methods
        int getLength() const;
        std::vector<Segment*> getSegments() const;

        bool isHorizontal() const;
        void changeOrientation();
        bool isDestroyed() const;
        
        void setCoordinate(Coordinate coordinate);
        
        void printStatus() const;        
};
