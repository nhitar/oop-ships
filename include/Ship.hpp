#pragma once

#include "Structs.hpp"

#include <iostream>
#include <vector>

class Ship {
    private:
        int length;
        Orientation orientation;
        std::vector<Segment> segments;
    public:
        Ship(int length);

        int getLength() const;
        Segment* getSegment(int index);

        bool isHorizontal() const;
        void setOrientation(Orientation newOrientation);
        bool isDestroyed() const;
        
        void setCoordinate(Coordinate coordinate);
};
