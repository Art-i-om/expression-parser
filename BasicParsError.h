#pragma once
#include <stdexcept>

class BasicParsError : std::runtime_error {
    using std::runtime_error::runtime_error;
};