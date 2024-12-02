#pragma once

#include <exception>

class HashMismatchException : public std::exception {
    public:
        const char* what() const noexcept override { return "Savefile has been interrupted and now you can't load it!"; }
};