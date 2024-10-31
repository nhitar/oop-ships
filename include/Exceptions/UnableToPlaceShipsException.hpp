#pragma once

#include <exception>

class UnableToPlaceShipsException : public std::exception {
    public:
        const char* what() const noexcept override { return "Can't place ships in such field!"; }
};