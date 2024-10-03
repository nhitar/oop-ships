#pragma once

#include "Ship.hpp"

enum class Orientation { Horizontal, Vertical };

enum class SegmentHealth { Untouched, Damaged, Destroyed };

enum class CellState { Hidden, Revealed };

enum class CellValue : char {
  ShipPart = 'S',
  Hit = 'X',
  Destroyed = '#',
  WaterHidden = '~',
  WaterRevealed = '*'
};

struct Coordinate {
    int x;
    int y;
};

struct Segment {
    Coordinate coordinate;
    SegmentHealth health;
};

struct Cell {
    Coordinate coordinate;
    CellState state;
    CellValue value;
    Segment* segment = nullptr;
};