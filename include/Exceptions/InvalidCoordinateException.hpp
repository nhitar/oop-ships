#pragma once

#include <exception>

class InvalidCoordinateException : public std::exception {
    public:
        const char* what() const noexcept override { return "Invalid input. Please enter integers for x and y!"; }
};