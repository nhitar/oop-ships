#include "../include/Ship.hpp"

Ship::Ship(int length) : length(length) {
    this->orientation = Orientation::Horizontal;
    for (int i = 0; i < length; i++) {
        this->segments.push_back(new Segment());
    }
}

Ship::~Ship() {
    for (auto& segment : this->segments) {
        delete segment;
    }
}

int Ship::getLength() const { 
    return this->length;
}

std::vector<Segment*> Ship::getSegments() const {
    return this->segments;
}

bool Ship::isHorizontal() const {
    if (this->orientation == Orientation::Horizontal) {
        return true;
    }
    return false;
}

void Ship::changeOrientation() {
    if (this->orientation == Orientation::Horizontal) {
        this->orientation = Orientation::Vertical;
        return;
    }
    this->orientation = Orientation::Horizontal;
}

bool Ship::isDestroyed() const {
    for (auto& segment : this->segments) {
        if (segment->health != SegmentHealth::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::setCoordinate(Coordinate coordinate) {
    int i = 0;
    for (auto& segment : this->segments) {
        if (this->orientation == Orientation::Horizontal) {
            segment->coordinate.x = coordinate.x + i;
            segment->coordinate.y = coordinate.y;
        } else {
            segment->coordinate.x = coordinate.x;
            segment->coordinate.y = coordinate.y + i;
        }
        ++i;
    }
}

void Ship::printStatus() const {
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

    std::vector<Segment*> segments = this->getSegments();
    for (auto segment : segments) {
        switch(segment->health) {
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