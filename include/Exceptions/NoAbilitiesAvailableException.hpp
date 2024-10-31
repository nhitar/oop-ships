#pragma once

#include <exception>

class NoAbilitiesAvailableException : public std::exception {
    public:
        const char* what() const noexcept override { return "There are no abilities available right now!"; }
};