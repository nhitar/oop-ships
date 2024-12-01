#include "../include/Wrapper.hpp"

Wrapper::Wrapper(const std::string& filename) : file(filename) {};

Wrapper::~Wrapper() {
    if (file.is_open())
        file.close();
}

void Wrapper::read(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file >> j;
}

void Wrapper::write(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file << j.dump(4);
}