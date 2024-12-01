#include "../include/Ship.hpp"

Ship::Ship(int length) : length(length) {
    this->orientation = Orientation::Horizontal;
    for (int i = 0; i < length; i++) {
        this->segments.push_back(Segment());
    }
}

int Ship::getLength() const { 
    return this->length;
}

Segment* Ship::getSegment(int index) {
    return &this->segments[index];
}

bool Ship::isHorizontal() const {
    if (this->orientation == Orientation::Horizontal) {
        return true;
    }
    return false;
}

void Ship::setOrientation(Orientation newOrientation) {
    if (newOrientation == Orientation::Horizontal) {
        this->orientation = Orientation::Vertical;
        return;
    }
    this->orientation = Orientation::Horizontal;
}

bool Ship::isDestroyed() const {
    for (auto& segment : this->segments) {
        if (segment.health != SegmentHealth::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::setCoordinate(Coordinate coordinate) {
    int i = 0;
    for (auto& segment : this->segments) {
        if (this->orientation == Orientation::Horizontal) {
            segment.coordinate.x = coordinate.x + i;
            segment.coordinate.y = coordinate.y;
        } else {
            segment.coordinate.x = coordinate.x;
            segment.coordinate.y = coordinate.y + i;
        }
        ++i;
    }
}