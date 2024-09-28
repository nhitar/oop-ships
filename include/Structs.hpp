#pragma once

enum class CellState {
    Hidden,
    Revealed
};

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

struct Cell {
    Coordinate coordinate;
    CellState state;
    CellValue value;
};