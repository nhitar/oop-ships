#include "../include/Ship.hpp"

Ship::Ship(int length) : length(length) {
    if (length < 1 || length > 4) {
        throw std::invalid_argument("Length of ship must be between 1 and 4");
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

void Ship::changeOrientation() {
    switch (this->orientation) {
        case Orientation::Horizontal:
            this->orientation = Orientation::Vertical;
            break;
        case Orientation::Vertical:
            this->orientation = Orientation::Horizontal;
            break;
    }
}

void Ship::applyDamage(Coordinate coordinate) {
    for (auto& segment : this->segments) {
        if (segment->coordinate.x == coordinate.x && segment->coordinate.y == coordinate.y) {
            if (segment->health == SegmentHealth::Untouched) {
                segment->health = SegmentHealth::Damaged;
            } else if (segment->health == SegmentHealth::Damaged) {
                segment->health = SegmentHealth::Destroyed;
            }
            return;
        }
    }
    std::cout << "Coordinate is out of range or miss" << std::endl;
}

bool Ship::isDestroyed() const {
    for (auto& segment : this->segments) {
        if (segment->health != SegmentHealth::Destroyed) {
            return false;
        }
    }
    return true;
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
    for (auto segment : segments)
        std::cout << segment << std::endl;
}