#pragma once

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

class Wrapper {
    std::fstream file;
public:
    Wrapper(const std::string& filename);

    ~Wrapper();

    void read(nlohmann::json& j);
    void write(nlohmann::json& j);
};