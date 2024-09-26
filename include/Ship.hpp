#pragma once

#include <vector>

enum class Orientation {
    Horizontal,
    Vertical
};
enum class SegmentHealth {
    Untouched,
    Damaged,
    Destroyed  
};

class Ship {
    private:
        int length;
        Orientation orientation;
        std::vector<SegmentHealth> segments;
    public:
        Ship(int length, Orientation orientation);
        //methods
        int getLength() const;
        void applyDamage(Coordinate coordinate);
        bool isDestroyed() const;
        void printStatus() const;
        
};