#pragma once

#include <exception>

class MultipleMissesException : public std::exception {
    public:
        const char* what() const noexcept override { return "Too much misses without success!"; }
};