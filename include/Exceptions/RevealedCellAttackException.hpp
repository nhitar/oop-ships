#pragma once

#include <exception>

class RevealedCellAttackException : public std::exception {
    public:
        const char* what() const noexcept override { return "Attempt to attack already revealed cell!"; }
};