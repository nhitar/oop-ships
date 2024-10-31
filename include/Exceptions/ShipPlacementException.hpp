#pragma once

#include <exception>

class ShipPlacementException : public std::exception {
    public:
        const char* what() const noexcept override { return "Incorrect ship placement!"; }
};