#pragma once

#include <iostream>
#include <vector>
#include "Structs.hpp"

enum class Orientation {
    Horizontal,
    Vertical
};

enum class SegmentHealth {
    Untouched,
    Damaged,
    Destroyed  
};

struct Segment {
    SegmentHealth health;
    Coordinate coordinate;
};

class Ship {
    private:
        int length;
        Orientation orientation;
        std::vector<Segment*> segments;
    public:
        Ship(int length);
        ~Ship();
        //methods
        int getLength() const;
        std::vector<Segment*> getSegments() const;
        void changeOrientation();
        void applyDamage(Coordinate coordinate);
        bool isDestroyed() const;
        void printStatus() const;
        
};