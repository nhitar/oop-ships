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

void Ship::printStatus()  {
    std::cout << "length: " << this->length  << std::endl;
    switch(this->orientation) {
        case Orientation::Horizontal:
            std::cout << "orientation: horizontal" << std::endl;
            break;
        case Orientation::Vertical:
            std::cout << "orientation: vertical" << std::endl;
            break;
    }
    std::cout << "Segments health:" << std::endl;

    for (int i = 0; i < this->length; i++) {
        switch(getSegment(i)->health) {
            case SegmentHealth::Untouched:
                std::cout << "Untouched" << std::endl;
                break;
            case SegmentHealth::Damaged:
                std::cout << "Damaged" << std::endl;
                break;
            case SegmentHealth::Destroyed:
                std::cout << "Destroyed" << std::endl;
                break;
        }    
    }
}