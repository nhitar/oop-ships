#pragma once

#include <exception>

class OutOfRangeException : public std::exception {
    public:
        const char* what() const noexcept override { return "Out of field range!"; }
};